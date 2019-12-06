#include "Window.h"
#include "WinException.h"
#include "resource.h"

Window::Window(Vector2i size, const std::wstring & title)
	: position({ 100, 100 })
	, size(size)
	, title(title)
	, done(false)
{
	HICON icon = static_cast<HICON>(LoadImageW(THIS_HINSTANCE, MAKEINTRESOURCEW(IDI_ICON1), IMAGE_ICON, 64, 64, 0));
	WNDCLASSEXW window = {};
	window.cbSize = sizeof(WNDCLASSEX);
	window.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	window.lpfnWndProc = WindowCallbackSetup;
	window.hInstance = THIS_HINSTANCE;
	window.lpszClassName = title.c_str();
	window.hIcon = icon;
	window.hIconSm = static_cast<HICON>(LoadImageW(THIS_HINSTANCE, MAKEINTRESOURCEW(IDI_ICON1), IMAGE_ICON, 16, 16, 0));


	RegisterClassExW(&window);

	//Adjust the window rect, so that we have a TRUE client size
	RECT rect = { position.x, position.y, position.x + size.x, position.y + size.y};
	DWORD style = WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE;
	AdjustWindowRect(&rect, style, false);
	
	//Create the window
	handle = CreateWindowExW(
		0, window.lpszClassName, title.c_str(), style,
		CW_USEDEFAULT, CW_USEDEFAULT,
		rect.right - rect.left, rect.bottom - rect.top,
		0, 0, THIS_HINSTANCE, this);

	if (!handle)
		throw WIN_EXCEPTION(GetLastError());
}

Window::~Window()
{
	DestroyWindow(handle);
}

void Window::set_title(const std::wstring& title)
{
	this->title = title;
	SetWindowTextW(handle, title.c_str());
}

bool Window::is_done() const
{
	return done;
}

void Window::close() 
{
	done = true;
}

HWND Window::get_handle() const
{
	return handle;
}

LRESULT Window::callback_function(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
	switch (msg)
	{
	case WM_SYSKEYDOWN:
	case WM_KEYDOWN:
	{
		bool is_repeated_down = l_param & (1 << 30);
		if (!is_repeated_down || keybd.is_autorepeat_set())
		{
			keybd.on_key_pressed((unsigned char)w_param);
		}
		break;
	}
	case WM_SYSKEYUP:
	case WM_KEYUP:
	{
		keybd.on_key_released((unsigned char)w_param);
		break;
	}
	case WM_CHAR:
	{
		keybd.on_char((unsigned char)w_param);
		break;
	}
	case WM_MOUSEMOVE:
	{
		POINTS pos = MAKEPOINTS(l_param);

		//Check whether mouse is inside the client area
		//and thus capture it and trigger on_enter once
		if (pos.x >= 0 &&
			pos.x < size.x &&
			pos.y >= 0 &&
			pos.y < size.y)
		{
			mouse.on_move({ pos.x, pos.y });
			if (!mouse.is_focused())
			{
				SetCapture(handle);
				mouse.on_enter({ pos.x, pos.y });
			}
		}
		//If not release the mouse and stop creating events
		else
		{
			if (w_param & (MK_LBUTTON | MK_RBUTTON))
			{
				mouse.on_move({ pos.x, pos.y });
			}
			else
			{
				ReleaseCapture();
				mouse.on_leave({ pos.x, pos.y });
			}
		}

		break;
	}
	case WM_LBUTTONDOWN:
	{
		POINTS pos = MAKEPOINTS(l_param);
		mouse.on_left_pressed({ pos.x, pos.y });
		break;
	}
	case WM_LBUTTONUP:
	{
		POINTS pos = MAKEPOINTS(l_param);
		mouse.on_left_released({ pos.x, pos.y });
		break;
	}	
	case WM_RBUTTONDOWN:
	{
		POINTS pos = MAKEPOINTS(l_param);
		mouse.on_right_pressed({ pos.x, pos.y });
		break;
	}
	case WM_RBUTTONUP:
	{
		POINTS pos = MAKEPOINTS(l_param);
		mouse.on_right_released({ pos.x, pos.y });
		break;
	}	
	case WM_MOUSEWHEEL:
	{
		POINTS pos = MAKEPOINTS(l_param);
		int mb_state = GET_KEYSTATE_WPARAM(w_param); //The current state of the mouse buttons
		//High order contains the distance the wheel has been rotated
		int delta = GET_WHEEL_DELTA_WPARAM(w_param);
		delta /= WHEEL_DELTA;
		mouse.on_scroll({ pos.x, pos.y }, delta);
		break;
	}
	case WM_KILLFOCUS:
	{
		keybd.clear_state();
		mouse.clear_state();
		break;
	}
	case WM_CLOSE:
	{
		done = true;
		PostQuitMessage(0);
		break;
	}
	}
	return DefWindowProcW(hwnd, msg, w_param, l_param);
}

LRESULT Window::WindowCallbackSetup(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
	if (msg == WM_NCCREATE)
	{
		//Get the this pointer passed in from the CreateWindowExW 
		CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(l_param);
		Window* const pWindow = reinterpret_cast<Window*>(pCreate->lpCreateParams);
		//Store the this pointer to the class
		SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
		//Set the normal windows callback now
		SetWindowLongPtrW(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::WindowCallbackDiverter));
		return pWindow->callback_function(hwnd, msg, w_param, l_param);
	}
	return DefWindowProcW(hwnd, msg, w_param, l_param);
}

LRESULT Window::WindowCallbackDiverter(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
	//Redirect the call to the window specific callback
	Window* const pWindow = reinterpret_cast<Window*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
	return pWindow->callback_function(hwnd, msg, w_param, l_param);
}


#pragma once
#include "GearsWin.h"
#include <string>
#include <functional>
#include "Keyboard.h"
#include "Mouse.h"
#include "Vector.h"

//Define a global variable called __ImageBase, which only works with
//Microsoft compiler, has the value of the hInstance
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define THIS_HINSTANCE ((HINSTANCE)&__ImageBase)

class Window
{
public:
	Window(Vector2i size, const std::wstring& title);
	Window(const Window&) = delete;
	~Window();

	void set_title(const std::wstring& title);

	bool is_done() const;

	void close();
	HWND get_handle() const;
	
	virtual LRESULT CALLBACK callback_function(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);
	
public:
	Keyboard keybd;
	Mouse mouse;

private:
	static LRESULT CALLBACK WindowCallbackSetup(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);
	static LRESULT CALLBACK WindowCallbackDiverter(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);

private:
	std::wstring title;
	Vector2i position;
	Vector2i size;

	HWND handle;
	bool done;

};


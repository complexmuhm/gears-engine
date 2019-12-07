#include "Engine.h"
#include <cmath>

Engine::Engine(Vector2i size, const std::wstring& title)
	: window(size, title)
	, gfx(window.get_handle())
{
}

void Engine::run()
{
	while (!window.is_done())
	{
		process_events();
		update();
		render();
	}
}

void Engine::process_events()
{
	MSG msg = {};
	while (PeekMessageW(&msg, window.get_handle(), 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	if (window.keybd.is_key_pressed(VK_ESCAPE))
	{
		window.close();
	}
}

void Engine::update()
{
}

void Engine::render()
{
	gfx.start(0.f, 0.f, 0.f, 1.0f);

	Vector2i mouse_pos = window.mouse.get_position();
	gfx.test((float)mouse_pos.x, (float)mouse_pos.y);
	
	gfx.end();
}

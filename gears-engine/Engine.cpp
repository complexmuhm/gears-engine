#include "Engine.h"
#include <cmath>

Engine::Engine(Vector2i size, const std::wstring& title)
	: window(size, title)
	, gfx(window.get_handle())
{
	edge_cuboid = std::make_unique<EdgeCuboid>(
		gfx,
		1.0f, 1.0f, 1.0f,
		1.f / window.get_aspect_ratio(), 0.5f, 100.f);
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
	static float theta = 0.0f;
	theta += 0.005f;

	edge_cuboid->set_rotation(theta, theta * 0.5f, theta * 0.5f * 0.5f);
	edge_cuboid->set_position(0.f, 0.f, 2.0f);
	edge_cuboid->update(0.f);
}

void Engine::render()
{
	gfx.start(0.f, 0.f, 0.f, 1.0f);

	edge_cuboid->draw(gfx);
	
	gfx.end();
}

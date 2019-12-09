#include "Engine.h"
#include <cmath>

Engine::Engine(Vector2i size, const std::wstring& title)
	: window(size, title)
	, gfx(window.get_handle())
{
	DirectX::XMStoreFloat4x4(&orthoGUI, 
		DirectX::XMMatrixOrthographicLH(
			(float)size.x, (float)size.y, 
			z_nearGUI, z_farGUI));
	DirectX::XMStoreFloat4x4(&proj,
		DirectX::XMMatrixPerspectiveFovLH(
			FOV, window.get_aspect_ratio(),
			z_near, z_far));
	edge_cuboid = std::make_unique<EdgeCuboid>(gfx, 1.0f, 1.0f, 1.0f, &proj);
	edge_cuboid->set_scale(10.f, 10.f, 10.f);
	label = std::make_unique<Text2D>(gfx, 0.f, 0.f, "Testing THIS text.", &orthoGUI);
	label->set_scale(2.f, 2.f);
	label->set_position(-640.f, 360.f);
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
	static float dt = 0.0f;
	theta += 0.005f;

	if (window.keybd.is_key_pressed(VK_SPACE))
		theta = 0.f;

	edge_cuboid->set_rotation(theta, theta * 0.5f, theta * 0.5f * 0.5f);
	edge_cuboid->set_position(0.f, 0.f, 100.f - theta);

	label->set_text(std::to_string(theta) + " s");
}

void Engine::render()
{
	gfx.start(0.f, 0.f, 0.f, 1.0f);

	edge_cuboid->draw(gfx);
	label->draw(gfx);
	
	gfx.end();
}

#include "Engine.h"
#include <cmath>


static float theta = 0.0f;
static float theta_inc = 0.005f;
static float dt = 0.0f;

Engine::Engine(Vector2i size, const std::wstring& title)
	: window(size, title)
	, gfx(window.get_handle())
{
	DirectX::XMStoreFloat4x4(&view,
		DirectX::XMMatrixIdentity());
	DirectX::XMStoreFloat4x4(&ortho, 
		DirectX::XMMatrixOrthographicLH(
			(float)size.x, (float)size.y, 
			z_nearGUI, z_farGUI));
	DirectX::XMStoreFloat4x4(&proj,
		DirectX::XMMatrixPerspectiveFovLH(
			FOV, window.get_aspect_ratio(),
			z_near, z_far));

	gui_manager = std::make_unique<GUIManager>(gfx, &view, &ortho);
	auto var = GUIManager::WIDGET_TABLE.at("Button_Var_Modifier");
	Button* var_modifier = dynamic_cast<Button*>(var);
	var_modifier->bind_left(std::bind([](float* theta) { *theta = 0.f; }, &theta));
	var_modifier->bind_middle(std::bind([](float* theta_inc) { *theta_inc = 0.05f;  }, &theta_inc));
	var_modifier->bind_right(std::bind([](float* theta_inc) { *theta_inc = 0.005f; }, &theta_inc));
	GUIManager::WIDGET_TABLE["Button_Close_Window"]->bind_left(std::bind(&Window::close, &window));

	edge_cuboid = std::make_unique<EdgeCuboid>(gfx, 1.0f, 1.0f, 1.0f, &view, &proj);
	edge_cuboid->set_scale(10.f, 10.f, 10.f);
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


	while (!window.keybd.empty() || !window.mouse.empty())
	{
		Keyboard::Event key_event = window.keybd.pop();
		Mouse::Event mouse_event = window.mouse.pop();

		gui_manager->process_events(key_event, mouse_event);
	}

	if (window.keybd.is_key_pressed(VK_ESCAPE))
	{
		window.close();
	}
}

void Engine::update()
{
	gui_manager->update(0.f);

	theta += theta_inc;

	if (window.keybd.is_key_pressed(VK_SPACE))
		theta = 0.f;

	edge_cuboid->set_rotation(theta, theta * 0.5f, theta * 0.5f * 0.5f);
	edge_cuboid->set_position(0.f, 0.f, 100.f - theta);

}

void Engine::render()
{
	gfx.start(0.f, 0.f, 0.f, 1.0f);

	edge_cuboid->draw(gfx);
	gui_manager->draw(gfx);
	
	gfx.end();
}

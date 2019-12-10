#include "GUIManager.h"

GUIManager::GUIManager(
	D3DGFX& gfx,
	const DirectX::XMFLOAT4X4* view,
	const DirectX::XMFLOAT4X4* ortho)
{
	std::vector<std::unique_ptr<Button>> buttons;
	buttons.emplace_back(std::make_unique<Button>(gfx, "Button", view, ortho));
	buttons.back()->bind_left([]() {});
	buttons.emplace_back(std::make_unique<Button>(gfx, "Button", view, ortho));
	buttons.back()->bind_left([]() {});
	buttons.emplace_back(std::make_unique<Button>(gfx, "Button", view, ortho));
	buttons.back()->bind_left([]() {});
	buttons.emplace_back(std::make_unique<Button>(gfx, "Button", view, ortho));
	buttons.back()->bind_left([]() {});
	buttons.emplace_back(std::make_unique<Button>(gfx, "Button", view, ortho));
	buttons.back()->bind_left([]() {});
	buttons.emplace_back(std::make_unique<Button>(gfx, "Button", view, ortho));
	buttons.back()->bind_left([]() {});
	buttons.emplace_back(std::make_unique<Button>(gfx, "Button", view, ortho));
	buttons.back()->bind_left([]() {});
	buttons.emplace_back(std::make_unique<Button>(gfx, "Button", view, ortho));
	buttons.back()->bind_left([]() {});
	buttons.emplace_back(std::make_unique<Button>(gfx, "Button", view, ortho));
	buttons.back()->bind_left([]() {});
	buttons.emplace_back(std::make_unique<Button>(gfx, "Button", view, ortho));
	buttons.back()->bind_left([]() {});
	buttons.emplace_back(std::make_unique<Button>(gfx, "Button", view, ortho));
	buttons.back()->bind_left([]() {});
	buttons.emplace_back(std::make_unique<Button>(gfx, "Button", view, ortho));
	buttons.back()->bind_left([]() {});
	buttons.emplace_back(std::make_unique<Button>(gfx, "Modify", view, ortho));
	register_gui_id("Button_Var_Modifier", buttons.back().get());
	buttons.emplace_back(std::make_unique<Button>(gfx, "Close", view, ortho));
	register_gui_id("Button_Close_Window", buttons.back().get());

	auto v_menu = std::make_unique<VMenu>(gfx, "EPS Menu", std::move(buttons), view, ortho);
	v_menu->set_scale(2.f, 2.f);

	widgets.emplace_back(std::move(v_menu));
	widgets.back()->set_position(0.f, 0.f);
}

void GUIManager::process_events(Keyboard::Event key_event, Mouse::Event mouse_event)
{
	for (auto& w : widgets)
	{
		w->process_events(key_event, mouse_event);
	}
}

void GUIManager::update(float dt)
{
	for (auto& w : widgets)
	{
		w->update(dt);
	}
}

#include <chrono>
#include <fstream>

void GUIManager::draw(D3DGFX& gfx)
{
	auto start = std::chrono::system_clock::now();
	for (auto& w : widgets)
	{
		w->draw(gfx);
	}
	auto end = std::chrono::system_clock::now();

	std::chrono::nanoseconds diff = end - start;
	
	static std::ofstream ofs("benchmark.dat");
	ofs << diff.count() << "\n";
}

void GUIManager::register_gui_id(const std::string& name, Widget* widget)
{
	WIDGET_TABLE.emplace(name, widget);
}

std::unordered_map<std::string, Widget*> GUIManager::WIDGET_TABLE;

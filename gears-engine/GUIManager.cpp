#include "GUIManager.h"
#include "Label.h"
#include "Button.h"
#include "VBox.h"

GUIManager::GUIManager(
	D3DGFX& gfx,
	const DirectX::XMFLOAT4X4* view,
	const DirectX::XMFLOAT4X4* ortho)
{
	auto v_box = std::make_unique<VBox>(gfx, "EPS Menu", view, ortho);
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
	buttons.emplace_back(std::make_unique<Button>(gfx, "Button", view, ortho));
	buttons.back()->bind_left([]() {});
	buttons.emplace_back(std::make_unique<Button>(gfx, "Button", view, ortho));
	buttons.back()->bind_left([]() {});

	for (auto& b : buttons)
		v_box->add_widget(std::move(b));

	v_box->set_scale(2.0f, 2.0f);
	widgets.emplace_back(std::move(v_box));
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
//6 elements -diff{ _MyRep = 3976 }		std::chrono::duration<__int64, std::ratio<1, 10000000>>
//24 elements +	diff	{_MyRep=6235 }	std::chrono::duration<__int64,std::ratio<1,  10000000>>
// +		diff	{_MyRep=15866 }	std::chrono::duration<__int64,std::ratio<1,10000000>>


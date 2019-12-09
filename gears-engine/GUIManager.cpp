#include "GUIManager.h"
#include "Label.h"
#include "Button.h"

GUIManager::GUIManager(
	D3DGFX& gfx,
	const DirectX::XMFLOAT4X4* view,
	const DirectX::XMFLOAT4X4* ortho)
{
	elements.emplace_back(std::make_unique<Label>(gfx, "Hello", view, ortho));
	elements.back()->set_scale(2.f, 2.f);
	elements.back()->set_position(0.f, 0.f, Transform2D::TOP_LEFT);

	float label_x = elements.back()->get_position(Transform2D::CENTER_CENTER).x;

	elements.emplace_back(std::make_unique<Button>(gfx, "Test", view, ortho));
	elements.back()->set_scale(2.0f, 2.0f);
	elements.back()->set_position(label_x, elements[elements.size() - 2]->get_position(Transform2D::BOTTOM_LEFT).y, Transform2D::TOP_CENTER);
	elements.emplace_back(std::make_unique<Button>(gfx, "Test", view, ortho));
	elements.back()->set_scale(2.0f, 2.0f);
	elements.back()->set_position(label_x, elements[elements.size() - 2]->get_position(Transform2D::BOTTOM_LEFT).y, Transform2D::TOP_CENTER);
	elements.emplace_back(std::make_unique<Button>(gfx, "Test", view, ortho));
	elements.back()->set_scale(2.0f, 2.0f);
	elements.back()->set_position(label_x, elements[elements.size() - 2]->get_position(Transform2D::BOTTOM_LEFT).y, Transform2D::TOP_CENTER);
	elements.emplace_back(std::make_unique<Button>(gfx, "Test", view, ortho));
	elements.back()->set_scale(2.0f, 2.0f);
	elements.back()->set_position(label_x, elements[elements.size() - 2]->get_position(Transform2D::BOTTOM_LEFT).y, Transform2D::TOP_CENTER);
	elements.emplace_back(std::make_unique<Button>(gfx, "Test", view, ortho));
	elements.back()->set_scale(2.0f, 2.0f);
	elements.back()->set_position(label_x, elements[elements.size() - 2]->get_position(Transform2D::BOTTOM_LEFT).y, Transform2D::TOP_CENTER);
	elements.emplace_back(std::make_unique<Button>(gfx, "Test", view, ortho));
	elements.back()->set_scale(2.0f, 2.0f);
	elements.back()->set_position(label_x, elements[elements.size() - 2]->get_position(Transform2D::BOTTOM_LEFT).y, Transform2D::TOP_CENTER);
	elements.emplace_back(std::make_unique<Button>(gfx, "Test", view, ortho));
	elements.back()->set_scale(2.0f, 2.0f);
	elements.back()->set_position(label_x, elements[elements.size() - 2]->get_position(Transform2D::BOTTOM_LEFT).y, Transform2D::TOP_CENTER);
}

void GUIManager::process_events(Keyboard::Event key_event, Mouse::Event mouse_event)
{
	for (auto& x : elements)
	{
		x->process_events(key_event, mouse_event);
	}
}

void GUIManager::update(float dt)
{
	for (auto& x : elements)
	{
		x->update(dt);
	}
}

#include <chrono>

void GUIManager::draw(D3DGFX& gfx)
{
	auto start = std::chrono::system_clock::now();
	for (auto& x : elements)
	{
		x->draw(gfx);
	}
	auto end = std::chrono::system_clock::now();

	auto diff = end - start;
}
//6 elements -diff{ _MyRep = 3976 }		std::chrono::duration<__int64, std::ratio<1, 10000000>>
//24 elements +	diff	{_MyRep=6235 }	std::chrono::duration<__int64,std::ratio<1,  10000000>>


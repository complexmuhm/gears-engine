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

	elements.emplace_back(std::make_unique<Button>(gfx, "Test", view, ortho));
	elements.back()->set_position(0.f, elements[elements.size() - 2]->get_position(Transform2D::BOTTOM_LEFT).y);
	elements.back()->set_scale(2.0f, 2.0f);
	elements.emplace_back(std::make_unique<Button>(gfx, "Test", view, ortho));
	elements.back()->set_position(0.f, elements[elements.size() - 2]->get_position(Transform2D::BOTTOM_LEFT).y);
	elements.back()->set_scale(2.0f, 2.0f);
	elements.emplace_back(std::make_unique<Button>(gfx, "Test", view, ortho));
	elements.back()->set_position(0.f, elements[elements.size() - 2]->get_position(Transform2D::BOTTOM_LEFT).y);
	elements.back()->set_scale(2.0f, 2.0f);
	elements.emplace_back(std::make_unique<Button>(gfx, "Test", view, ortho));
	elements.back()->set_position(0.f, elements[elements.size() - 2]->get_position(Transform2D::BOTTOM_LEFT).y);
	elements.back()->set_scale(2.0f, 2.0f);
	elements.emplace_back(std::make_unique<Button>(gfx, "Test", view, ortho));
	elements.back()->set_position(0.f, elements[elements.size() - 2]->get_position(Transform2D::BOTTOM_LEFT).y);
	elements.back()->set_scale(2.0f, 2.0f);
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

void GUIManager::draw(D3DGFX& gfx)
{
	for (auto& x : elements)
	{
		x->draw(gfx);
	}
}

#include "GUIManager.h"
#include "Label.h"

GUIManager::GUIManager(
	D3DGFX& gfx,
	const DirectX::XMFLOAT4X4* view,
	const DirectX::XMFLOAT4X4* ortho)
{
	elements.emplace_back(std::make_unique<Label>(gfx, "Hello", view, ortho));

	elements.front()->bind_enter([]() { OutputDebugStringA("Enter.\n"); });
	elements.front()->bind_leave([]() { OutputDebugStringA("Leave.\n"); });
	elements.front()->bind_left([]() { OutputDebugStringA("Left.\n"); });
	elements.front()->bind_right([]() { OutputDebugStringA("Right.\n"); });
	elements.front()->bind_middle([]() { OutputDebugStringA("Middle.\n"); });

	elements.front()->set_scale(4.f, 4.f);
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

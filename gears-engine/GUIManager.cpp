#include "GUIManager.h"

GUIManager::GUIManager()
{
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

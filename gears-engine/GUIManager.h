#pragma once

#include "Widget.h"
#include <vector>

class GUIManager
{
public:
	GUIManager(
		D3DGFX& gfx,
		const DirectX::XMFLOAT4X4* view,
		const DirectX::XMFLOAT4X4* ortho);

	GUIManager(const GUIManager&) = delete;
	GUIManager& operator=(const GUIManager&) = delete;

	void process_events(Keyboard::Event key_event, Mouse::Event mouse_event);
	void update(float dt);
	void draw(D3DGFX& gfx);

private:
	std::vector<std::unique_ptr<Widget>> elements;

};


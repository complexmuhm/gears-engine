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

	Widget* get_widget(size_t GUI_ID); // TODO: implemente register_gui_id() and get_widget() with a unordered_map

private:
	void register_gui_id(const std::string& name, size_t GUI_ID);

private:
	std::vector<std::unique_ptr<Widget>> widgets;

};


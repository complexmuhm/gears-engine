#pragma once

#include "Widget.h"
#include "Label.h"
#include "Button.h"
#include "VBox.h"

class VMenu : public Widget
{
public:
	VMenu(
		D3DGFX& gfx,
		const std::string& title,
		std::vector<std::unique_ptr<Button>> buttons,
		const DirectX::XMFLOAT4X4* view,
		const DirectX::XMFLOAT4X4* ortho);

	VMenu(const VMenu&) = delete;
	VMenu& operator=(const VMenu&) = delete;

	void process_events(Keyboard::Event key_event, Mouse::Event mouse_event) override;
	void update(float dt) override;
	void draw(D3DGFX& gfx) override;

	virtual void set_position(float x, float y, Transform2D::RELPOS relative_pos = Transform2D::TOP_LEFT) override;
	virtual void set_scale(float x, float y) override;
	virtual void set_rotation(float angle) override;
	virtual void set_dimension(float length, float height) override;

	void toggle();

private:
	void minimize();
	void maximize();

private:
	Vector2i old_mpos, new_mpos;
	bool is_minimized;

	Label title;
	std::vector<std::unique_ptr<Button>> buttons;
	std::vector<Widget*> widgets;
	VBox organizer;
	
};


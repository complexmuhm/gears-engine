#pragma once

#include "Widget.h"

class VBox : public Widget 
{
public:
	// TODO: give option to align the buttons left, center, right
	// maybe try to implement constraints too? (not here)
	enum RELPOS
	{
		ALIGN_LEFT,
		ALIGN_CENTER,
		ALIGN_RIGHT
	};

	VBox(
		D3DGFX& gfx,
		const std::string& text,
		const DirectX::XMFLOAT4X4* view,
		const DirectX::XMFLOAT4X4* ortho);

	VBox(const VBox&) = delete;
	VBox& operator=(const VBox&) = delete;

	void process_events(Keyboard::Event key_event, Mouse::Event mouse_event) override;
	void update(float dt) override;
	void draw(D3DGFX& gfx) override;

	void add_widget(Widget* widget);

	virtual void set_position(float x, float y, Transform2D::RELPOS relative_pos = Transform2D::TOP_LEFT) override;
	virtual void set_scale(float x, float y) override;
	virtual void set_rotation(float angle) override;
	virtual void set_dimension(float length, float height) override;

private:
	void adjust_widgets();

private:
	std::vector<Widget*> widgets;
	// TODO: add padding and margin functionality
	
};


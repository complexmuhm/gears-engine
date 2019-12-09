#pragma once

#include "Widget.h"
#include "Text2D.h"

class Button : public Widget
{
public:
	Button(
		D3DGFX& gfx, const std::string& text,
		const DirectX::XMFLOAT4X4* view,
		const DirectX::XMFLOAT4X4* ortho);

	void update(float dt) override;
	void draw(D3DGFX& gfx) override;

	virtual void set_position(float x, float y, RELPOS relative_pos = RELPOS::TOP_LEFT) override;
	virtual void set_scale(float x, float y) override;
	virtual void set_rotation(float angle) override;
	virtual void set_dimension(float length, float height) override;

	void set_text(const std::string& text);

private:
	void synchronize();

private:
	Text2D text;
	Vector4f color_current;
	Vector4f color_normal, color_hover, color_pressed;

	

private:

};


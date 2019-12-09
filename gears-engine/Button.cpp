#include "Button.h"

Button::Button(
	D3DGFX& gfx,
	const std::string& text,
	const DirectX::XMFLOAT4X4* view,
	const DirectX::XMFLOAT4X4* ortho)
	: Widget(view, ortho)
	, text(gfx, 0.f, 0.f, text, view, ortho)
	, color_current({ 1.0f, 1.0f, 1.0f, 1.0f })
	, color_normal({ 1.0f, 1.0f, 1.0f, 1.0f })
	, color_hover({ 0.7f, 0.7f, 0.7f, 1.0f })
	, color_pressed({ 0.4f, 0.4f, 0.4f, 1.0f })
{
	synchronize();
}

void Button::update(float dt)
{
	if (!hasEntered)
		color_current = color_normal;
	if (isHovering)
		color_current = color_hover;
	if (hasPressed)
		color_current = color_pressed;

	text.set_color(color_current);

}

void Button::draw(D3DGFX& gfx)
{
	text.draw(gfx);
}

void Button::set_position(float x, float y, RELPOS relative_pos)
{
	Transform2D::set_position(x, y, relative_pos);
	text.set_position(x, y, relative_pos);
}

void Button::set_scale(float x, float y)
{
	Transform2D::set_scale(x, y);
	text.set_scale(x, y);
}

void Button::set_rotation(float angle)
{
	Transform2D::set_rotation(angle);
	text.set_rotation(angle);
}

void Button::set_dimension(float length, float height)
{
	Transform2D::set_dimension(length, height);
	text.set_dimension(length, height);
}

void Button::set_text(const std::string& text)
{
	this->text.set_text(text);
	synchronize();
}

void Button::synchronize()
{
	float length = 0.f, height = 0.f;
	this->text.get_dimension(length, height);
	set_dimension(length, height);
}

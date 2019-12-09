#include "Label.h"

Label::Label(
	D3DGFX& gfx, const std::string& text,
	const DirectX::XMFLOAT4X4* view,
	const DirectX::XMFLOAT4X4* ortho)
	: Widget(view, ortho)
	, text(gfx, 0.f, 0.f, text, view, ortho)
{
	synchronize();
}

void Label::update(float dt)
{
}

void Label::draw(D3DGFX& gfx)
{
	text.draw(gfx);
}

void Label::set_position(float x, float y, RELPOS relative_pos)
{
	Transform2D::set_position(x, y, relative_pos);
	text.set_position(x, y, relative_pos);
}

void Label::set_scale(float x, float y)
{
	Transform2D::set_scale(x, y);
	text.set_scale(x, y);
}

void Label::set_rotation(float angle)
{
	Transform2D::set_rotation(angle);
	text.set_rotation(angle);
}

void Label::set_dimension(float length, float height)
{
	Transform2D::set_dimension(length, height);
	text.set_dimension(length, height);
}

void Label::set_text(const std::string& text)
{
	this->text.set_text(text);
	synchronize();
}

void Label::synchronize()
{
	float length = 0.f, height = 0.f;
	this->text.get_dimension(length, height);
	set_dimension(length, height);
}

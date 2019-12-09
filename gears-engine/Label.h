#pragma once

#include "Widget.h"
#include "Text2D.h"

class Label : public Widget
{
public:
	Label(
		D3DGFX& gfx, const std::string& text,
		const DirectX::XMFLOAT4X4* view,
		const DirectX::XMFLOAT4X4* ortho);

	void update(float dt) override;
	void draw(D3DGFX& gfx) override;

	virtual void set_position(float x, float y, RELPOS relative_pos = RELPOS::TOP_LEFT) override;
	virtual void set_scale(float x, float y) override;
	virtual void set_rotation(float angle) override;
	virtual void set_dimension(float length, float height) override;


private:
	Text2D text;
};


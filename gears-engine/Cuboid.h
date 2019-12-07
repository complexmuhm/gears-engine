#pragma once

#include "Drawable.h"
#include "Transform.h"

class Cuboid : public Drawable, public Transform
{
public:
	Cuboid(D3DGFX& gfx, float length, float height, float width);

	void update(float dt) override;

private:
	float length, width, height;

};


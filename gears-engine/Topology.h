#pragma once

#include "Bindable.h"

class Topology : public Bindable
{
public:
	Topology(D3DGFX& gfx, D3D11_PRIMITIVE_TOPOLOGY topol);

	void bind() override;

private:
	D3D11_PRIMITIVE_TOPOLOGY topology;

};


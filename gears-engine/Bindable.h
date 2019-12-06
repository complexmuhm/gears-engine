#pragma once
#include "D3DGFX.h"

class Bindable
{
public:
	Bindable(D3DGFX& gfx);
	virtual void bind(D3DGFX& gfx) = 0;
	virtual ~Bindable() = default;

protected:
	ID3D11DeviceContext* get_device_context();
	ID3D11Device* get_device();

private:
	D3DGFX& gfx;
};


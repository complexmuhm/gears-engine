#pragma once
#include "D3DGFX.h"
#include "D3DException.h"

class Bindable
{
public:
	Bindable(D3DGFX& gfx);
	virtual void bind() = 0;
	virtual ~Bindable() = default;

protected:
	ID3D11DeviceContext* get_device_context();
	ID3D11Device* get_device();

private:
	D3DGFX& gfx;
};


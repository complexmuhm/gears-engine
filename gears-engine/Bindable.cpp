#include "Bindable.h"

Bindable::Bindable(D3DGFX& gfx)
	: gfx(gfx)
{
}

ID3D11DeviceContext* Bindable::get_device_context()
{
	return gfx.device_context.Get();
}

ID3D11Device* Bindable::get_device()
{
	return gfx.device.Get();
}

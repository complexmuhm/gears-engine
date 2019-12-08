#include "Sampler.h"

Sampler::Sampler(D3DGFX& gfx)
	: Bindable(gfx)
{
	HRESULT result;

	D3D11_SAMPLER_DESC sampler_desc = {};
	sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	result = get_device()->CreateSamplerState(&sampler_desc, &sampler);
	D3D_EXCEPTION(result);
}

void Sampler::bind()
{
	get_device_context()->PSSetSamplers(0u, 1u, sampler.GetAddressOf());
}

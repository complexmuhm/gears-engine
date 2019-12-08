#pragma once

#include "Bindable.h"

class Sampler : public Bindable
{
public:
	Sampler(D3DGFX& gfx);
	Sampler(const Sampler&) = delete;
	Sampler& operator=(const Sampler&) = delete;

	void bind() override;

private:
	wrl::ComPtr<ID3D11SamplerState> sampler;

};


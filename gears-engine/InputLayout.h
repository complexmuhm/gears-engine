#pragma once

#include "Bindable.h"

class InputLayout : public Bindable
{
public:
	// TODO: Allow to input a vector of D3D11INPUT_ELEMENT_DESC
	InputLayout(D3DGFX& gfx, ID3DBlob* compiled_shader);

	void bind() override;

private:
	wrl::ComPtr<ID3D11InputLayout> input_layout;
};


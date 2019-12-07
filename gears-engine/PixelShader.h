#pragma once

#include "Bindable.h"

class PixelShader : public Bindable
{
public:
	PixelShader(D3DGFX& gfx, const wchar_t* compiled_shader_filename);
	
	void bind() override;

private:
	wrl::ComPtr<ID3D11PixelShader> pixel_shader;
};

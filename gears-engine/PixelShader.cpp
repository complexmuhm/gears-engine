#include "PixelShader.h"

PixelShader::PixelShader(D3DGFX& gfx, const wchar_t* compiled_shader_filename)
	: Bindable(gfx)
{
	HRESULT result;
	wrl::ComPtr<ID3DBlob> compiled_shader;
	result = D3DReadFileToBlob(compiled_shader_filename, &compiled_shader);
	D3D_EXCEPTION(result);

	result = get_device()->CreatePixelShader(
		compiled_shader->GetBufferPointer(),
		compiled_shader->GetBufferSize(),
		nullptr, &pixel_shader);
	D3D_EXCEPTION(result);
}

void PixelShader::bind()
{
	get_device_context()->PSSetShader(pixel_shader.Get(), nullptr, 0u);
}

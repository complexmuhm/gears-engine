#include "VertexShader.h"

VertexShader::VertexShader(D3DGFX& gfx, const wchar_t* compiled_shader_filename)
	: Bindable(gfx)
{
	HRESULT result;

	result = D3DReadFileToBlob(compiled_shader_filename, &compiled_shader);
	D3D_EXCEPTION(result);
	
	result = get_device()->CreateVertexShader(
		compiled_shader->GetBufferPointer(),
		compiled_shader->GetBufferSize(),
		nullptr, &vertex_shader);
	D3D_EXCEPTION(result);
}

void VertexShader::bind()
{
	get_device_context()->VSSetShader(vertex_shader.Get(), nullptr, 0u);
}

ID3DBlob* VertexShader::get_compiled_shader() const
{
	return compiled_shader.Get();
}

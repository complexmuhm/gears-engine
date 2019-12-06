#include "InputLayout.h"

InputLayout::InputLayout(D3DGFX& gfx, ID3DBlob* compiled_shader)
	: Bindable(gfx)
{
	HRESULT result;

	const D3D11_INPUT_ELEMENT_DESC in_element_desc[] =
	{
		{"Position", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u},
		{"Color"   , 0u, DXGI_FORMAT_R32G32B32A32_FLOAT, 0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u}
	};

	result = get_device()->CreateInputLayout(
		in_element_desc, (UINT)std::size(in_element_desc),
		compiled_shader->GetBufferPointer(), compiled_shader->GetBufferSize(),
		&input_layout);
	D3D_EXCEPTION(result);
}

void InputLayout::bind()
{
	get_device_context()->IASetInputLayout(input_layout.Get());
}

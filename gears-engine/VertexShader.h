#pragma once

#include "Bindable.h"

class VertexShader : public Bindable
{
public:
	VertexShader(D3DGFX& gfx, const wchar_t* shader_binary);
	
	void bind() override;

	ID3DBlob* get_compiled_shader() const;

private:
	wrl::ComPtr<ID3DBlob> compiled_shader;
	wrl::ComPtr<ID3D11VertexShader> vertex_shader;
};


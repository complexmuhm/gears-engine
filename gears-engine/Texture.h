#pragma once

#include "Bindable.h"
#include "Extern/picopng.h"

class Texture : public Bindable
{
public:
	Texture(D3DGFX& gfx, const std::string& filename);
	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;

	void bind() override;

private:
	wrl::ComPtr<ID3D11ShaderResourceView> texture;
};


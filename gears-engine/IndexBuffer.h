#pragma once

#include "Bindable.h"
#include <vector>

class IndexBuffer : public Bindable
{
public:
	IndexBuffer(D3DGFX& gfx, std::vector<UINT> indices);

	void bind() override;
	
	UINT count() const;
private:
	UINT index_size;
	wrl::ComPtr<ID3D11Buffer> index_buffer;
};


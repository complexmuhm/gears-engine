#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(D3DGFX& gfx, const std::vector<UINT>& indices)
	: Bindable(gfx)
	, index_size((UINT)indices.size())
{
	D3D11_BUFFER_DESC desc = {};
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.ByteWidth = sizeof(UINT) * index_size;
	desc.StructureByteStride = sizeof(UINT);
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA data = {};
	data.pSysMem = indices.data();

	get_device()->CreateBuffer(&desc, &data, &index_buffer);
}

void IndexBuffer::bind()
{
	get_device_context()->IASetIndexBuffer(index_buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
}

UINT IndexBuffer::count() const
{
	return index_size;
}

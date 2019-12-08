#include "VertexBuffer.h"
#include <cassert>

VertexBuffer::VertexBuffer(D3DGFX& gfx, const std::vector<Vertex>& vertices)
	: Bindable(gfx)
{
	assert(!vertices.empty());
	HRESULT result;

	D3D11_BUFFER_DESC desc = {};
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.ByteWidth = static_cast<UINT>(sizeof(Vertex) * vertices.size());
	desc.StructureByteStride = sizeof(Vertex);
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA data = {};
	data.pSysMem = vertices.data();

	result = get_device()->CreateBuffer(&desc, &data, &vertex_buffer);
	D3D_EXCEPTION(result);
}

void VertexBuffer::bind()
{
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0;
	get_device_context()->IASetVertexBuffers(
		0u, 1u, vertex_buffer.GetAddressOf(), 
		&stride, &offset);
}

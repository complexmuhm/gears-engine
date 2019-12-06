#pragma once

#include "Bindable.h"
#include "D3DException.h"

template<typename T>
class ConstantBuffer : public Bindable
{
public:
	ConstantBuffer(D3DGFX& gfx);
	ConstantBuffer(D3DGFX& gfx, const T& c_buffer);

	void update(const T& c_buffer);

protected:
	wrl::ComPtr<ID3D11Buffer> constant_buffer;
};

template<typename T>
ConstantBuffer<T>::ConstantBuffer(D3DGFX& gfx)
	: Bindable(gfx)
{
	HRESULT result;

	D3D11_BUFFER_DESC desc = {};
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.ByteWidth = sizeof(T);
	desc.StructureByteStride = 0u;
	desc.MiscFlags = 0u;

	result = get_device()->CreateBuffer(&desc, nullptr, &constant_buffer);
	D3D_EXCEPTION(result);
}

template<typename T>
ConstantBuffer<T>::ConstantBuffer(D3DGFX& gfx, const T& c_buffer)
{
	HRESULT result;

	D3D11_BUFFER_DESC desc = {};
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.ByteWidth = sizeof(T);
	desc.StructureByteStride = 0u;
	desc.MiscFlags = 0u;

	D3D11_SUBRESOURCE_DATA data = {};
	data.pSysMem = &c_buffer;

	result = get_device()->CreateBuffer(&desc, &data, &constant_buffer);
	D3D_EXCEPTION(result);
}

template<typename T>
void ConstantBuffer<T>::update(const T& c_buffer)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mapped_resource = {};
	result = get_device_context()->Map(
		constant_buffer.Get(), 0u, 
		D3D11_MAP_WRITE_DISCARD, 0u, 
		&mapped_resource);
	D3D_EXCEPTION(result);

	std::memcpy(mapped_resource.pData, &c_buffer, sizeof(T));
	get_device_context()->Unmap(constant_buffer.Get(), 0u);
}

template<typename T>
class VertexConstantBuffer : public ConstantBuffer<T>
{
	using ConstantBuffer<T>::constant_buffer;
	using Bindable::get_device_context;

public:
	using ConstantBuffer<T>::ConstantBuffer;

	void bind()
	{
		get_device_context()->VSSetConstantBuffers(0u, 1u, constant_buffer.GetAddressOf());
	}
};

template<typename T>
class PixelConstantBuffer : public ConstantBuffer<T>
{
	using ConstantBuffer<T>::constant_buffer;
	using Bindable::get_device_context;

public:
	using ConstantBuffer<T>::ConstantBuffer;

	void bind()
	{
		get_device_context()->PSSetConstantBuffers(0u, 1u, constant_buffer.GetAddressOf());
	}
};


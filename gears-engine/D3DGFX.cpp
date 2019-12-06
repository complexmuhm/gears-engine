#include "D3DGFX.h"
#include "D3DException.h"
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3Dcompiler.lib")

#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "InputLayout.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Topology.h"

D3DGFX::D3DGFX(HWND hwnd)
	: hwnd(hwnd)
{
	HRESULT result = 0;
	// description of EVERYTHING the swap chain offers
	DXGI_SWAP_CHAIN_DESC swap_chain_description = {};
	swap_chain_description.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swap_chain_description.BufferDesc.Width = 0;
	swap_chain_description.BufferDesc.Height = 0;
	swap_chain_description.BufferDesc.RefreshRate.Numerator = 0;
	swap_chain_description.BufferDesc.RefreshRate.Denominator = 0;
	swap_chain_description.BufferDesc.Scaling = DXGI_MODE_SCALING_CENTERED;
	swap_chain_description.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
	swap_chain_description.SampleDesc.Count = 1;
	swap_chain_description.SampleDesc.Quality = 0;
	swap_chain_description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap_chain_description.BufferCount = 1;
	swap_chain_description.OutputWindow = hwnd;
	swap_chain_description.Windowed = true;
	swap_chain_description.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swap_chain_description.Flags = 0;

	UINT flags = 0;
#ifndef NDEBUG
	flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	// Create the device + device context and swap chain to write to
	result = D3D11CreateDeviceAndSwapChain(
		nullptr, D3D_DRIVER_TYPE_HARDWARE,
		0, flags, nullptr, 0,
		D3D11_SDK_VERSION,
		&swap_chain_description,
		&swap_chain,
		&device, nullptr,
		&device_context);
	D3D_EXCEPTION(result);

	// Get the render target view to the back buffer to clear it
	wrl::ComPtr<ID3D11Resource> resource = nullptr;
	result = swap_chain->GetBuffer(0, __uuidof(ID3D11Resource), &resource);
	D3D_EXCEPTION(result);

	D3D11_RENDER_TARGET_VIEW_DESC view_desc = {};
	result = device->CreateRenderTargetView(resource.Get(), nullptr, &target_view);
	D3D_EXCEPTION(result);


}

D3DGFX::~D3DGFX()
{
}

void D3DGFX::start(float r, float g, float b, float a)
{
	float color[] = { r, g, b, a };
	device_context->ClearRenderTargetView(target_view.Get(), color);	
}

void D3DGFX::end()
{
	// TODO: check on DXGI_ERROR_DEVICE_REMOVED and try to recover from it
	swap_chain->Present(1u, 0);
}

void D3DGFX::test()
{
	IndexBuffer index_buffer(*this, {
			0, 1, 2,
			0, 2, 3,
			1, 5, 6,
			1, 6, 2,
			5, 4, 7,
			5, 7, 6,
			4, 0, 3,
			4, 3, 7,
			4, 5, 1,
			4, 1, 0,
			3, 2, 6,
			3, 6, 7
		});
	VertexBuffer vertex_buffer(*this, {
		{ -0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f},
		{  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f},
		{  0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f},
		{ -0.5f, -0.5f,  0.0f, 0.5f, 0.5f, 0.5f, 1.0f},
		{ -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f},
		{  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f},
		{  0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f},
		{ -0.5f, -0.5f,  1.0f, 0.5f, 0.5f, 0.5f, 1.0f}
		});
	VertexShader vertex_shader(*this, L"VertexShader.cso");
	InputLayout input_layout(*this, vertex_shader.get_compiled_shader());
	PixelShader pixel_shader(*this, L"PixelShader.cso");
	Topology topology(*this, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	RECT rect = {};
	GetClientRect(hwnd, &rect);
	long width = rect.right - rect.left;
	long height = rect.bottom - rect.top;
	float aspr = (float)(height) / (float)(width);

	static float theta = 0.0f;
	theta += 0.005f;

	struct cVertexBuffer
	{
		DirectX::XMMATRIX transformation;
	};

	cVertexBuffer cverbuf =
	{
		DirectX::XMMatrixTranspose(
		DirectX::XMMatrixRotationZ(theta) *
		DirectX::XMMatrixRotationX(theta) *
		DirectX::XMMatrixTranslation(0.0f, 0.0f, 4.0f) *
		DirectX::XMMatrixPerspectiveLH(1.0f, aspr, 0.5f, 10.f))
	};

	VertexConstantBuffer<cVertexBuffer> vertex_cbuffer(*this, cverbuf);

	struct cPixelBuffer
	{
		struct
		{
			float r, g, b, a;
		} face_colors[6];
	};

	cPixelBuffer cpixbuf =
	{
		{
			{1.0f, 0.0f, 1.0f, 1.0f},
			{1.0f, 0.0f, 0.0f, 1.0f},
			{0.0f, 1.0f, 0.0f, 1.0f},
			{0.0f, 0.0f, 1.0f, 1.0f},
			{1.0f, 1.0f, 0.0f, 1.0f},
			{0.0f, 1.0f, 1.0f, 1.0f}
		}
	};

	PixelConstantBuffer<cPixelBuffer> pixel_cbuffer(*this, cpixbuf);

	std::vector<Bindable*> list;
	list.push_back(&index_buffer);
	list.push_back(&vertex_buffer);
	list.push_back(&vertex_shader);
	list.push_back(&input_layout);
	list.push_back(&pixel_shader);
	list.push_back(&topology);
	list.push_back(&vertex_cbuffer);
	list.push_back(&pixel_cbuffer);

	for (auto& x : list)
		x->bind();



	// Set the render target to the render target view that we have created at the ctor
	device_context->OMSetRenderTargets(1u, target_view.GetAddressOf(), nullptr);

	// Create the viewport

	D3D11_VIEWPORT viewport = {};
	viewport.Width = (float)width;
	viewport.Height = (float)height;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;
	device_context->RSSetViewports(1u, &viewport);
	

	device_context->DrawIndexed(index_buffer.size(), 0u, 0u);
}


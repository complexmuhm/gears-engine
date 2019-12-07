#include "D3DGFX.h"
#include "D3DException.h"
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3Dcompiler.lib")

#include "ConstantBuffer.h"
#include "Cuboid.h"
#include "EdgeCuboid.h"

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
	result = device->CreateRenderTargetView(resource.Get(), nullptr, &render_view);
	D3D_EXCEPTION(result);

	// Create depth stencil state, (depth buffer)
	D3D11_DEPTH_STENCIL_DESC depth_stencil_desc = {};
	depth_stencil_desc.DepthEnable = true;
	depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depth_stencil_desc.DepthFunc = D3D11_COMPARISON_LESS;

	wrl::ComPtr<ID3D11DepthStencilState> depth_stencil_state;
	result = device->CreateDepthStencilState(
		&depth_stencil_desc, &depth_stencil_state);
	D3D_EXCEPTION(result);

	device_context->OMSetDepthStencilState(
		depth_stencil_state.Get(), 1u);

	RECT rect = {};
	GetClientRect(hwnd, &rect);
	long width = rect.right - rect.left;
	long height = rect.bottom - rect.top;

	// Create the depth texture2d 
	wrl::ComPtr<ID3D11Texture2D> texture2d;
	D3D11_TEXTURE2D_DESC texture2d_desc = {};
	texture2d_desc.Width = width;
	texture2d_desc.Height = height;
	texture2d_desc.MipLevels = 1u;
	texture2d_desc.ArraySize = 1u;
	texture2d_desc.Format = DXGI_FORMAT_D32_FLOAT; //D for depth
	texture2d_desc.SampleDesc.Count = 1u;
	texture2d_desc.SampleDesc.Quality = 0u;
	texture2d_desc.Usage = D3D11_USAGE_DEFAULT;
	texture2d_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	result = device->CreateTexture2D(
		&texture2d_desc, nullptr, &texture2d);
	D3D_EXCEPTION(result);

	// Create the depth view
	D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc = {};
	depth_stencil_view_desc.Format = DXGI_FORMAT_D32_FLOAT;
	depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depth_stencil_view_desc.Texture2D.MipSlice = 0u;

	result = device->CreateDepthStencilView(
		texture2d.Get(), &depth_stencil_view_desc,
		&depth_view);
	D3D_EXCEPTION(result);

	// Bind the depth stencil view and the render target view	
	device_context->OMSetRenderTargets(
		1u, render_view.GetAddressOf(), depth_view.Get());

	// Create the viewport
	D3D11_VIEWPORT viewport = {};
	viewport.Width = (float)width;
	viewport.Height = (float)height;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;
	device_context->RSSetViewports(1u, &viewport);
}

D3DGFX::~D3DGFX()
{
}

void D3DGFX::start(float r, float g, float b, float a)
{
	float color[] = { r, g, b, a };
	device_context->ClearRenderTargetView(
		render_view.Get(), color);	
	device_context->ClearDepthStencilView(
		depth_view.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

void D3DGFX::draw_indexed(UINT index_count)
{
	device_context->DrawIndexed(index_count, 0u, 0u);
}

void D3DGFX::end()
{
	// TODO: check on DXGI_ERROR_DEVICE_REMOVED and try to recover from it
	swap_chain->Present(1u, 0);
}

void D3DGFX::test(float x, float y)
{
	//D3D11_RASTERIZER_DESC rasterizer_desc = {};
	//rasterizer_desc.FillMode = D3D11_FILL_WIREFRAME;
	//rasterizer_desc.CullMode = D3D11_CULL_NONE;
	//rasterizer_desc.DepthClipEnable = true;
	//device->CreateRasterizerState(&rasterizer_desc, &rasterizer_state);
	//device_context->RSSetState(rasterizer_state.Get());
}


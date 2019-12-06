#include "D3DGFX.h"
#include <sstream>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3Dcompiler.lib")

#define GFX_EXCEPTION(x) if(FAILED(x)){throw D3DGFX::D3DException(__LINE__, __FILE__, x);}


D3DGFX::D3DGFX(HWND hwnd)
	: hwnd(hwnd)
{
	HRESULT result = 0;
	//description of EVERYTHING the swap chain offers
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
	//Create the device + device context and swap chain to write to
	result = D3D11CreateDeviceAndSwapChain(
		nullptr, D3D_DRIVER_TYPE_HARDWARE,
		0, flags, nullptr, 0,
		D3D11_SDK_VERSION,
		&swap_chain_description,
		&swap_chain,
		&device, nullptr,
		&device_context);
	GFX_EXCEPTION(result);

	//Get the render target view to the back buffer to clear it
	wrl::ComPtr<ID3D11Resource> resource = nullptr;
	result = swap_chain->GetBuffer(0, __uuidof(ID3D11Resource), &resource);
	GFX_EXCEPTION(result);

	D3D11_RENDER_TARGET_VIEW_DESC view_desc = {};
	result = device->CreateRenderTargetView(resource.Get(), nullptr, &target_view);
	GFX_EXCEPTION(result);


}

D3DGFX::~D3DGFX()
{
}

void D3DGFX::start(Vector4f color)
{
	device_context->ClearRenderTargetView(target_view.Get(), reinterpret_cast<float*>(&color));	
}

void D3DGFX::end()
{
	//TODO: check on DXGI_ERROR_DEVICE_REMOVED and try to recover from it
	swap_chain->Present(1u, 0);
}

void D3DGFX::test()
{
	HRESULT result;
	struct Vertex
	{
		float x, y, z;
		float r, g, b, a;
	};

	const Vertex v[] = {
		{ -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f },
		{  0.0f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f },
		{  0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f }
	};

	//Create the buffer
	D3D11_BUFFER_DESC vertex_buffer_desc = {};
	vertex_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	vertex_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertex_buffer_desc.ByteWidth = sizeof(v);
	vertex_buffer_desc.StructureByteStride = sizeof(Vertex);
	vertex_buffer_desc.CPUAccessFlags = 0;
	vertex_buffer_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertex_buffer_data = {};
	vertex_buffer_data.pSysMem = v;

	wrl::ComPtr<ID3D11Buffer> vertex_buffer;
	result = device->CreateBuffer(&vertex_buffer_desc, &vertex_buffer_data, &vertex_buffer);

	//Set the pipeline state
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0;
	device_context->IASetVertexBuffers(0, 1, vertex_buffer.GetAddressOf(), &stride, &offset);
	//Set the topology
	device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	//Get the compiled vertex shader and set it in the pipeline
	wrl::ComPtr<ID3DBlob> compiled_shader;
	D3DReadFileToBlob(L"VertexShader.cso", &compiled_shader);

	wrl::ComPtr<ID3D11VertexShader> vertex_shader;
	device->CreateVertexShader(
		compiled_shader->GetBufferPointer(), 
		compiled_shader->GetBufferSize(), 
		nullptr, &vertex_shader);
	device_context->VSSetShader(vertex_shader.Get(), nullptr, 0u);

	//Set the input layout for the vertex shader
	wrl::ComPtr<ID3D11InputLayout> input_layout;
	const D3D11_INPUT_ELEMENT_DESC input_element_desc[] =
	{
		{"Position", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u},
		{"Color", 0u, DXGI_FORMAT_R32G32B32A32_FLOAT, 0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u}
	};
	device->CreateInputLayout(
		input_element_desc, (UINT)std::size(input_element_desc), 
		compiled_shader->GetBufferPointer(), compiled_shader->GetBufferSize(),
		&input_layout);
	device_context->IASetInputLayout(input_layout.Get());

	//Get the compiled pixel shader and set it in the pipeline
	D3DReadFileToBlob(L"PixelShader.cso", &compiled_shader);
	wrl::ComPtr<ID3D11PixelShader> pixel_shader;
	device->CreatePixelShader(
		compiled_shader->GetBufferPointer(),
		compiled_shader->GetBufferSize(),
		nullptr, &pixel_shader);
	device_context->PSSetShader(pixel_shader.Get(), nullptr, 0u);
	
	device_context->OMSetRenderTargets(1u, target_view.GetAddressOf(), nullptr);

	//Create the viewport
	RECT rect = {};
	GetClientRect(hwnd, &rect);
	long width = rect.right - rect.left;
	long height = rect.bottom - rect.top;

	D3D11_VIEWPORT viewport = {};
	viewport.Width = (float)width;
	viewport.Height = (float)height;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;
	device_context->RSSetViewports(1u, &viewport);


	device_context->Draw((UINT)std::size(v), 0);
}


//EXCEPTION=============================================================================
D3DGFX::D3DException::D3DException(
	int line, const char* file, 
	HRESULT result, std::vector<std::string> msgs) noexcept
	: BaseException(line, file)
	, result(result)
{
	if (!msgs.empty())
	{
		//Form a chain out of the messages
		for (const auto& m : msgs)
		{
			info += m;
			info.push_back('\n');
		}
		info.pop_back();
	}
}

const char* D3DGFX::D3DException::what() const noexcept
{
	std::stringstream ss;
	ss << "[" << result << "] " << get_error() << "\n";
	ss << "[Error] " << get_error() << "\n";
	ss << "[Description] " << get_error_description() << "\n";
	if (!info.empty())
	{
		ss << "\n[Info]\n" << get_error_info() << "\n";
	}
	ss << "\n" << get_content();
	what_buffer = ss.str();
	return what_buffer.c_str();
}

const char* D3DGFX::D3DException::get_type() const noexcept
{
	return "DirectX Exception";
}

HRESULT D3DGFX::D3DException::get_error_code() const noexcept
{
	return result;
}

std::string D3DGFX::D3DException::get_error() const noexcept
{
	//return DXGetErrorStringA(result);
	return "lol";
}

std::string D3DGFX::D3DException::get_error_description() const noexcept
{
	//char buffer[1024];
	//DXGetErrorDescriptionA(result, buffer, sizeof(buffer));
	//return buffer;
	return "double lol";
}

std::string D3DGFX::D3DException::get_error_info() const noexcept
{
	return info;
}

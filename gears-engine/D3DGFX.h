#pragma once
#include <D3D11.h>
#include <wrl.h>
//#include <xnamath.h> //For SSE optimized vectors, matrices etc.
#include <d3dcompiler.h>

namespace wrl = Microsoft::WRL;

class D3DGFX
{
	friend class Bindable;
public:

public:
	D3DGFX(HWND hwnd);
	D3DGFX(const D3DGFX&) = delete;
	D3DGFX& operator=(const D3DGFX&) = delete;
	~D3DGFX();

	void start(float r, float g, float b, float a);
	void draw_indexed(UINT index_count);
	void end();

	void test(float x, float y);

private:
	HWND hwnd;
#ifndef NDEBUG
	//DXGIDebugInfoManager debug_info;
#endif
	wrl::ComPtr<IDXGISwapChain> swap_chain;
	wrl::ComPtr<ID3D11Device> device;
	wrl::ComPtr<ID3D11DeviceContext> device_context;
	wrl::ComPtr<ID3D11RenderTargetView> render_view;
	wrl::ComPtr<ID3D11DepthStencilView> depth_view;

};


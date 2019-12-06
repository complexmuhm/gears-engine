#pragma once
#include <D3D11.h>
#include <wrl.h>
//#include <xnamath.h> //For SSE optimized vectors, matrices etc.
#include <vector>
#include <string>
#include "BaseException.h"
#include "Vector.h"

namespace wrl = Microsoft::WRL;

class D3DGFX
{
public:
	class D3DException : public BaseException
	{
	public:
		D3DException(int line, const char* file, HRESULT result, std::vector<std::string> msgs = {}) noexcept;

		const char* what() const noexcept override;
		const char* get_type() const noexcept override;
		HRESULT get_error_code() const noexcept;
		std::string get_error() const noexcept;
		std::string get_error_description() const noexcept;
		std::string get_error_info() const noexcept;

	private:
		HRESULT result;
		std::string info;
	};

public:
	D3DGFX(HWND hwnd);
	D3DGFX(const D3DGFX&) = delete;
	D3DGFX& operator=(const D3DGFX&) = delete;
	~D3DGFX();

	void start(Vector4f color);
	void end();

	void test();

private:
#ifndef NDEBUG
	//DXGIDebugInfoManager debug_info;
#endif
	wrl::ComPtr<IDXGISwapChain> swap_chain;
	wrl::ComPtr<ID3D11Device> device;
	wrl::ComPtr<ID3D11DeviceContext> device_context;
	wrl::ComPtr<ID3D11RenderTargetView> target_view;

};


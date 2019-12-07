#pragma once

#include <Windows.h>
#include <vector>
#include <string>
#include "BaseException.h"

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

#define D3D_EXCEPTION(x) if(FAILED(x)) { throw D3DException(__LINE__, __FILE__, x); }

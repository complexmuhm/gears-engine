#pragma once

#include "WinException.h"
#include "D3DException.h"

class Exception : public BaseException
{
public:
	Exception(int line, const char* filename, const char* error) noexcept;

	const char* what() const noexcept override;
	virtual const char* get_type() const noexcept;

private:
	std::string error;

};

#define EXCEPTION(x) Exception(__LINE__, __FILE__, std::string(x).c_str())

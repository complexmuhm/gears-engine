#pragma once
#include "GearsWin.h"
#include "BaseException.h"

class WinException : public BaseException
{
public:
	WinException(int line, const char* filename, HRESULT result) noexcept;

	const char* what() const noexcept override;
	virtual const char* get_type() const noexcept;

	static std::string translate_win_error(HRESULT result) noexcept;
	HRESULT get_error_code() const noexcept;
	std::string get_formatted_win_error() const noexcept;

private:
	HRESULT result;
};

#define WIN_EXCEPTION(x) WinException(__LINE__, __FILE__, x)
#define WIN_EXCEPTION_LAST() WIN_EXCEPTION(GetLastError())


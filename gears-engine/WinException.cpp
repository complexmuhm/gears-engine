#include "WinException.h"
#include <sstream>

WinException::WinException(int line, const char * filename, HRESULT result) noexcept
	: BaseException(line, filename)
	, result(result)
{
}

const char * WinException::what() const noexcept
{
	std::stringstream ss;
	ss << "[" << result << "] " << get_formatted_win_error() << "\n\n" << get_content();
	what_buffer = ss.str();
	return what_buffer.c_str();
}

const char * WinException::get_type() const noexcept
{
	return "Windows Exception";
}

std::string WinException::translate_win_error(HRESULT result) noexcept
{
	char* msg_buffer = nullptr;
	DWORD msg_length = FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, result,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
		reinterpret_cast<LPSTR>(&msg_buffer), 0, nullptr);
	
	if (msg_length == 0)
	{
		return "Unknown Error.";
	}

	std::string formatted_string(msg_buffer);
	LocalFree(msg_buffer);

	return formatted_string;
}

HRESULT WinException::get_error_code() const noexcept
{
	return result;
}

std::string WinException::get_formatted_win_error() const noexcept
{
	return translate_win_error(result);
}



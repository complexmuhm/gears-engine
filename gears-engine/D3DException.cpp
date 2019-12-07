#include "D3DException.h"
#include <sstream>

D3DException::D3DException(
	int line, const char* file, 
	HRESULT result, std::vector<std::string> msgs) noexcept
	: BaseException(line, file)
	, result(result)
{
	if (!msgs.empty())
	{
		// Form a chain out of the messages
		for (const auto& m : msgs)
		{
			info += m;
			info.push_back('\n');
		}
		info.pop_back();
	}
}

const char* D3DException::what() const noexcept
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

const char* D3DException::get_type() const noexcept
{
	return "DirectX Exception";
}

HRESULT D3DException::get_error_code() const noexcept
{
	return result;
}

// TODO: Implement a real god damn function that gives more info than "lol"
// or "double lol"
std::string D3DException::get_error() const noexcept
{
	//return DXGetErrorStringA(result);
	return "lol";
}

std::string D3DException::get_error_description() const noexcept
{
	//char buffer[1024];
	//DXGetErrorDescriptionA(result, buffer, sizeof(buffer));
	//return buffer;
	return "double lol";
}

std::string D3DException::get_error_info() const noexcept
{
	return info;
}


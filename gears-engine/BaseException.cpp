#include "BaseException.h"
#include <sstream>

BaseException::BaseException(int line, const char * filename) noexcept
	:line(line), filename(filename)
{
}

const char* BaseException::what() const noexcept
{
	std::stringstream ss;
	ss << get_content();
	what_buffer = ss.str();
	return what_buffer.c_str();
}

const char * BaseException::get_type() const noexcept
{
	return "Base Exception";
}

int BaseException::get_line() const noexcept
{
	return line;
}

const std::string& BaseException::get_file() const noexcept
{
	return filename;
}

const std::string BaseException::get_content() const noexcept
{
	std::stringstream ss;
	ss << "(" << filename << ":" << line << ") ";
	return ss.str();
}

#include "Exceptions.h"

Exception::Exception(int line, const char* filename, const char* error) noexcept
	: BaseException(line, filename)
	, error(error)
{
}

const char* Exception::what() const noexcept
{
	what_buffer = "[Error] " + error + "\n\n"
					+ get_content();
	return what_buffer.c_str();
}

const char* Exception::get_type() const noexcept
{
	return "Exception";
}

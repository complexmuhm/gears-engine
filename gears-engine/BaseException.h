#pragma once
#include <exception>
#include <string>

class BaseException : public std::exception
{
public:
	BaseException(int line, const char* filename) noexcept;

	const char* what() const noexcept override;
	virtual const char* get_type() const noexcept;
	const std::string get_content() const noexcept;
	const std::string& get_file() const noexcept;
	int get_line() const noexcept;

protected:
	mutable std::string what_buffer;

private:
	int line;
	std::string filename;

};


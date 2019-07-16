#pragma once
#include <stdexcept>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

// throw an error with description of error code
[[noreturn]] inline void throw_error(std::string where)
{
	where += ": ";
	where += strerror(errno);
	throw std::runtime_error( where );
}


inline void check_would_block(const char* where)
{
	if (errno != EWOULDBLOCK)
		throw_error( where );
}

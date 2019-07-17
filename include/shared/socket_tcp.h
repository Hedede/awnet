#pragma once
#include <string>
#include <string_view>
#include <optional>
#include <shared/socket_inet.h>

namespace aw {
class socket_listener;

enum class socket_status {
	ok,
	closed,
	would_block
};

struct socket_tcp : socket {
	socket_tcp();

	socket_status receive(std::string& msg);
	void send(std::string_view what);

protected:
	friend class socket_listener;
	socket_tcp(int fd)
		: socket(fd)
	{}
};
} // namespace aw

#pragma once
#include <string>
#include <string_view>
#include <optional>
#include <shared/socket_inet.h>

namespace aw {
class socket_listener;
struct socket_tcp : socket {
	socket_tcp(ip4_address addr, std::uint16_t port);

	void listen(int backlog);
	void accept();

	std::string receive();
	void send(std::string_view what);

protected:
	friend class socket_listener;
	socket_tcp(int fd)
		: socket(fd)
	{}
};
} // namespace aw

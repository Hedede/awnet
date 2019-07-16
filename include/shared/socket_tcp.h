#pragma once
#include <string>
#include <string_view>
#include <optional>
#include <shared/address.h>

namespace aw {
class socket_listener;
struct socket_tcp {
	socket_tcp(ip4_address addr, std::uint16_t port);

	socket_tcp(socket_tcp const&) = delete;
	socket_tcp(socket_tcp&& other)
		: fd(other.fd)
	{
		other.fd = 0;
	}

	socket_tcp& operator=(socket_tcp const&) = delete;
	socket_tcp& operator=(socket_tcp&& other)
	{
		fd = other.fd;
		other.fd = 0;
		return *this;
	}


	~socket_tcp();

	void listen(int backlog);
	void accept();

	std::string receive();
	void send(std::string_view what);

protected:
	friend class socket_listener;
	socket_tcp(int fd)
		: fd(fd)
	{}

private:
	int fd;
};
} // namespace aw

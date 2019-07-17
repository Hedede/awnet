#include <shared/socket_inet.h>

#include <fcntl.h>

#include "error.h"
#include "address_util.h"


namespace aw {
socket::socket(protocol type)
{
	auto convert_type = [] (protocol proto) {
		if (proto == protocol::udp)
			return SOCK_DGRAM;
		return SOCK_STREAM;
	};
	fd = ::socket(AF_INET, convert_type(type), 0);
	if (fd == -1)
		throw_error("socket");

}

socket::~socket()
{
	close();
}

void socket::bind(ip4_address addr, std::uint16_t port)
{
	set_reuse_addr();
	auto sa = make_sockaddr_in(addr, port);
	auto err = ::bind(fd, (struct sockaddr*)&sa, sizeof(sa));
	if (err == -1)
		throw_error("bind");
}

void socket::connect(ip4_address addr, std::uint16_t port)
{
	auto sa = make_sockaddr_in(addr, port);
	auto err = ::connect(fd, (struct sockaddr*)&sa, sizeof(sa));
	if (err == -1)
		throw_error("connect");
}

void socket::close()
{
	if (fd != -1)
	{
		::close(fd);
		fd = -1;
	}
}



void socket::make_non_blocking()
{
	int flags = fcntl(fd, F_GETFL);
	if (flags == 0)
		throw_error("fcntl(F_GETFL)");

	int err = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
	if (err == -1)
		throw_error("fcntl(F_SETFL)");
}

void socket::set_reuse_addr()
{
	int reuse = 1;
	int err = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse));
	if (err == -1)
		throw_error("setsockopt");
}


socket_handle socket::handle() const
{
	return socket_handle(fd);
}

} // namespace aw

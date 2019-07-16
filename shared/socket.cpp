#include <shared/socket_inet.h>

#include <fcntl.h>

#include "error.h"
#include "address_convert.h"


namespace aw {
socket::socket(int type, ip4_address addr, std::uint16_t port)
{
	fd = ::socket(AF_INET, type, 0);
	if (fd == -1)
		throw_error("socket");

	auto sa = make_sockaddr_in(addr, port);
	int err = bind(fd, (struct sockaddr*)&sa, sizeof(sa));
	if (err == -1)
		throw_error("bind");

	int reuse = 1;
	err = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse));
	if (err == -1)
		throw_error("setsockopt");
}

socket::~socket()
{
	close();
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

socket_handle socket::handle() const
{
	return socket_handle(fd);
}

} // namespace aw

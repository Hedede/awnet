#include <shared/socket_tcp.h>
#include <shared/config.h>

#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>

#include "error.h"
#include "address_convert.h"

namespace aw {

socket_tcp::socket_tcp(ip4_address addr, std::uint16_t port)
{
	fd = ::socket(AF_INET, SOCK_STREAM, 0);
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


socket_tcp::~socket_tcp()
{
	close(fd);
}

std::string socket_tcp::receive()
{
	char buffer[MAX_MESSAGE_LENGTH];
	auto size = read(fd, buffer, sizeof(buffer));
	if (size == -1)
		throw_error("read");
	return {buffer, size_t(size)};
}

void socket_tcp::send(std::string_view what)
{
	auto err = write(fd, what.data(), what.size());
	if (err == -1)
		throw_error("write");
}
} // namespace aw

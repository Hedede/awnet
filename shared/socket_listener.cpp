#include <shared/socket_listener.h>
#include <shared/socket_tcp.h>

#include <unistd.h>
#include <sys/socket.h>
#include <stdio.h>
#include <fcntl.h>
#include <iostream>

#include "error.h"
#include "address_convert.h"

namespace aw {
socket_listener::socket_listener(ip4_address addr, std::uint16_t port, int backlog)
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

	err = ::listen(fd, backlog);
	if (err == -1)
		throw_error("listen");

	
	int flags = fcntl(fd, F_GETFL);
	if (flags == 0)
		throw_error("fcntl(F_GETFL)");

	err = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
	if (err == -1)
		throw_error("fcntl(F_SETFL)");
}


socket_listener::~socket_listener()
{
	close(fd);
}


std::optional<socket_tcp> socket_listener::accept()
{
	int data_socket = ::accept(fd, nullptr, nullptr);
	if (data_socket == -1) {
		check_would_block("accept");
		return std::nullopt;
	}
	std::cerr << "accepted connection from " << data_socket << '\n';
	return socket_tcp( data_socket );
}
} // namespace aw

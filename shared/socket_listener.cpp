#include <shared/socket_listener.h>

#include <unistd.h>
#include <sys/socket.h>
#include <stdio.h>
#include <fcntl.h>
#include <iostream>

#include "error.h"
#include "address_convert.h"

namespace aw {
socket_listener::socket_listener(ip4_address addr, std::uint16_t port, int backlog)
	: socket_tcp( addr, port )
{
	make_non_blocking();
	listen(backlog);
}


void socket_listener::listen(int backlog)
{
	int err = ::listen( get_fd(), backlog);
	if (err == -1)
		throw_error("listen");
}

std::optional<socket_tcp> socket_listener::accept()
{
	int data_socket = ::accept( get_fd(), nullptr, nullptr);
	if (data_socket == -1) {
		check_would_block("accept");
		return std::nullopt;
	}
	std::cerr << "accepted connection from " << data_socket << '\n';
	return socket_tcp( data_socket );
}
} // namespace aw

#include <shared/socket_tcp.h>
#include <shared/config.h>

#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>

#include "error.h"
#include "address_util.h"

namespace aw {

socket_tcp::socket_tcp(ip4_address addr, std::uint16_t port)
	: socket(SOCK_STREAM, addr, port)
{
}

std::string socket_tcp::receive()
{
	char buffer[MAX_MESSAGE_LENGTH];
	auto size = read( get_fd(), buffer, sizeof(buffer));
	if (size == -1)
		throw_error("read");
	return {buffer, size_t(size)};
}

void socket_tcp::send(std::string_view what)
{
	auto err = write( get_fd(), what.data(), what.size());
	if (err == -1)
		throw_error("write");
}
} // namespace aw

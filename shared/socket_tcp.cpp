#include <shared/socket_tcp.h>
#include <shared/config.h>

#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>

#include "error.h"
#include "address_util.h"

namespace aw {

socket_tcp::socket_tcp()
	: socket(protocol::tcp)
{
}

socket_status socket_tcp::receive(std::string& msg)
{
	char buffer[MAX_MESSAGE_LENGTH];
	auto size = read( get_fd(), buffer, sizeof(buffer));
	if (size == -1)
		throw_error("read");
	if (size == 0)
		return socket_status::closed;

	msg.assign(buffer, size_t(size));

	return socket_status::ok;
}

void socket_tcp::send(std::string_view what)
{
	auto err = write( get_fd(), what.data(), what.size());
	if (err == -1)
		throw_error("write");
}
} // namespace aw

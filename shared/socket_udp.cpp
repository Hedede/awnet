#include <shared/socket_udp.h>

#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>

#include <iostream>

#include <shared/config.h>

#include "error.h"
#include "address_util.h"

namespace aw {
socket_udp::socket_udp()
	: socket(protocol::udp)
{
}

static auto receive_impl( int fd, int flags, std::string& msg, ip4_address& addr, std::uint16_t& port)
{
	char buffer[MAX_MESSAGE_LENGTH];
	struct sockaddr_in sa { };
	socklen_t sa_len = sizeof(sa);

	auto size = recvfrom( fd, buffer, sizeof(buffer), flags, (struct sockaddr*)&sa, &sa_len);

	if (size != -1) {
		msg = std::string( buffer, size );

		extract_address( sa, addr, port );
	}

	return size;
}

std::string socket_udp::receive(ip4_address& addr, std::uint16_t& port)
{
	std::string msg;
	auto err = receive_impl( get_fd(), 0, msg, addr, port);

	if (err == -1)
		throw_error("receive");

	return msg;
}

std::optional<std::string> socket_udp::receive_async(ip4_address& addr, std::uint16_t& port)
{
	std::string msg;
	auto err = receive_impl( get_fd(), MSG_DONTWAIT, msg, addr, port);

	if (err == -1) {
		check_would_block("receive_async");
		return {};
	}

	return msg;
}

void socket_udp::send(std::string_view msg, ip4_address addr, std::uint16_t port)
{
	auto sa = make_sockaddr_in(addr, port);
	auto size = sendto(get_fd(), msg.data(), msg.size(), 0, (struct sockaddr*)&sa, sizeof(sa));
	if (size == -1)
		throw_error("send");
}
} // namespace aw

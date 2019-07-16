#include <shared/socket_datagram.h>
#include <shared/config.h>
#include "error.h"
#include "address_convert.h"

#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>

#include <iostream>
namespace aw {
socket_datagram::socket_datagram(ip4_address addr, std::uint16_t port)
{
	fd = ::socket(AF_INET, SOCK_DGRAM, 0);
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

socket_datagram::~socket_datagram()
{
	close(fd);
}

static auto receive_impl( int fd, int flags, std::string& msg, ip4_address& addr, std::uint16_t& port)
{
	char buffer[MAX_MESSAGE_LENGTH];
	struct sockaddr_in sa { };
	socklen_t sa_len = sizeof(sa);

	auto size = recvfrom(fd, buffer, sizeof(buffer), flags, (struct sockaddr*)&sa, &sa_len);

	if (size != -1) {
		msg = std::string( buffer, size );
		extract_address( sa, addr, port );
	}

	return size;
}

std::string socket_datagram::receive(ip4_address& addr, std::uint16_t& port)
{
	std::string msg;
	auto err = receive_impl( fd, 0, msg, addr, port);

	if (err == -1)
		throw_error("receive");

	return msg;
}

std::optional<std::string> socket_datagram::receive_async(ip4_address& addr, std::uint16_t& port)
{
	std::string msg;
	auto err = receive_impl( fd, MSG_DONTWAIT, msg, addr, port);

	if (err == -1) {
		check_would_block("receive_async");
		return {};
	}

	return msg;
}

void socket_datagram::send(std::string_view msg, ip4_address addr, std::uint16_t port)
{
	auto sa = make_sockaddr_in(addr, port);
	auto size = sendto(fd, msg.data(), msg.size(), 0, (struct sockaddr*)&sa, sizeof(sa));
	std::cerr << msg.data() << '\n';
	std::cerr << msg.size() << '\n';
	std::cerr << size << '\n';
	std::cerr << sizeof(sa) << '\n';
	std::cerr << addr << '\n';
	std::cerr << port << '\n';
	if (size == -1)
		throw_error("send");
}
} // namespace aw

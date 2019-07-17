#include <shared/address.h>

#include "address_util.h"

#include <stdexcept>
#include <iostream>

#include <arpa/inet.h>

namespace aw {
ip4_address parse_address(const char* str)
{
	ip4_address out;
	auto err = inet_pton(AF_INET, str, &out);
	if (err == -1)
		throw std::invalid_argument("Must supply a valid IPv4 address");
	return ntohl(out);
}

std::uint16_t parse_port(const char* str)
{
	auto port = std::stoul( str );
	if (port > 65535 || port < 1)
		throw std::range_error("Port must be a value in range 1-65536");
	return port;
}

std::string address_string(ip4_address addr)
{
	char buf[INET_ADDRSTRLEN];
	// addr = htonl(addr);
	inet_ntop(AF_INET, &addr, buf, sizeof(buf));
	return buf;
}

std::string describe_address(const struct sockaddr& sa)
{
	auto family = sa.sa_family;
	if (family == AF_INET)
		return address_string( ((struct sockaddr_in&)sa).sin_addr.s_addr );

	char buf[INET6_ADDRSTRLEN];
	auto in6_addr = &((struct sockaddr_in6&)sa).sin6_addr;
	inet_ntop(family, in6_addr, buf, sizeof(buf));
	return buf;
}

void log_address(std::ostream& os, const struct sockaddr_in& sa)
{
	std::cerr << describe_address((const struct sockaddr&)sa) << " port: " << ntohs( sa.sin_port ) << '\n';
}
} // namespace aw

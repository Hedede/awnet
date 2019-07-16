#include <shared/address.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace aw {
inline struct sockaddr_in make_sockaddr_in(ip4_address addr, std::uint16_t port)
{
	// use aggregate initialization to zero-initialize the struct
	struct sockaddr_in sa { };

	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = htonl(addr);
	sa.sin_port = htons(port);

	return sa;
}

inline void extract_address(struct sockaddr_in& sa, ip4_address& addr, std::uint16_t& port)
{
	addr = ntohl( sa.sin_addr.s_addr );
	port = ntohs( sa.sin_port );
}

inline std::string describe_address(struct sockaddr& sa)
{
	char buf[INET6_ADDRSTRLEN];
	auto family = sa.sa_family;
	if (family == AF_INET) {
		auto in_addr = &((struct sockaddr_in&)sa).sin_addr;
		inet_ntop(family, in_addr, buf, sizeof(buf));
	} else if (family == AF_INET6) {
		auto in6_addr = &((struct sockaddr_in6&)sa).sin6_addr;
		inet_ntop(family, in6_addr, buf, sizeof(buf));
	}
	return buf;
}
} // namespace aw

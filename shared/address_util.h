#include <shared/address.h>
#include <iosfwd>
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

std::string describe_address(const struct sockaddr& sa);
void log_address(std::ostream& os, const struct sockaddr_in& sa);
} // namespace aw

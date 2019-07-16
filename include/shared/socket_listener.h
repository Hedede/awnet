#pragma once
#include <string>
#include <string_view>
#include <optional>

#include <shared/socket_tcp.h>

namespace aw {
/*
 * Listens to TCP connections
 */
struct socket_listener : socket_tcp {
	// \param backlog
	//    maximum number of pending connections
	socket_listener(ip4_address addr, std::uint16_t port, int backlog);

	/* attempt to accept a connection
	 *
	 * \return
	 *    An object representing a TCP socket.
	 *    If there are no pending connections, nullopt is retuned.
	 */
	std::optional<socket_tcp> accept();

protected:
	void listen(int backlog);
};
} // namespace aw

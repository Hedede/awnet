#pragma once
#include <server/tcp_server.h>
#include <server/udp_server.h>
#include <server/socket_multiplexer.h>
#include <shared/address.h>

namespace aw {

struct server {
	server(ip4_address addr, std::uint16_t port);

	void run();

private:
	multiplexer mux;
	tcp_server tcp;
	udp_server udp;
};

} // namespace aw

#pragma once
#include <server/data_callback.h>
#include <server/client_connection.h>
#include <shared/socket_datagram.h>

namespace aw {
class multiplexer;

struct udp_server : data_callback {
	udp_server(ip4_address addr, std::uint16_t port, multiplexer& mux);

	void on_data_received() override;

private:
	socket_datagram sock;
};

} // namespace aw

#include <server/udp_server.h>
#include <server/number_parser.h>
#include <server/socket_multiplexer.h>
#include <shared/config.h>
#include <algorithm>
#include <iostream>

namespace aw {
udp_server::udp_server(ip4_address addr, std::uint16_t port, multiplexer& mux)
{
	sock.bind(addr, port);
	mux.add(sock.handle(), *this);
}

void udp_server::on_data_received()
{
	aw::ip4_address addr;
	std::uint16_t port;

	auto msg = sock.receive_async( addr, port );
	if (!msg)
		return;

	std::cerr << "received message from " << addr << " port: "<< port;

	auto response = aw::generate_response( std::string(*msg) );

	sock.send( response, addr, port );
}
} // namespace aw

#include <server/server.h>
#include <stdexcept>
#include <iostream>

namespace aw {
server::server(ip4_address addr, std::uint16_t port)
	: tcp(addr, port, mux), udp(addr, port, mux)
{
}

void server::run()
{
	while(true) try {
		mux.select();
		// clean up closed connections
		tcp.cleanup_connections();
	} catch( std::exception& ex ) {
		std::cerr << "error: " << ex.what() << '\n';
	}
}

} // namespace aw

#include <shared/socket_listener.h>
#include <shared/socket_tcp.h>
#include <shared/socket_datagram.h>

#include <server/number_parser.h>
#include <server/socket_multiplexer.h>

#include <thread>
#include <iostream>

int main(int, char** argv)
{
	{
		aw::socket_listener sock(0, 10000, 32);

		auto conn = sock.accept();
		do {
			conn = sock.accept();
		} while(!conn);

		auto msg = conn->receive( );

		auto response = aw::generate_response( std::string(msg) );

		conn->send( response );
	}

	{
		aw::socket_datagram sock(0, 10000);

		aw::ip4_address addr;
		std::uint16_t port;

		auto msg = sock.receive( addr, port );

		auto response = aw::generate_response( std::string(msg) );

		sock.send( response, addr, port );
	}
}

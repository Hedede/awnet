#include <server/tcp_server.h>
#include <shared/config.h>
#include <algorithm>
#include <iostream>

namespace aw {
tcp_server::tcp_server(ip4_address addr, std::uint16_t port, multiplexer& mux)
	: mux(mux), sock(addr, port, MAX_PENDING_CONNECTIONS)
{
	mux.add(sock.handle(), *this);
}

void tcp_server::on_data_received()
{
	auto conn = sock.accept();
	if (conn)
		create_connection( std::move(*conn) );
}

void tcp_server::cleanup_connections()
{
	for (auto conn : closed_connections)
		remove_connection( conn );
	closed_connections.clear();
}

void tcp_server::create_connection( socket_tcp&& conn )
{
	auto ptr = std::make_unique<client_connection>(std::move(conn), *this);
	mux.add( ptr->handle(), *ptr );
	connections.emplace_back( std::move(ptr) );
}

void tcp_server::on_connection_closed( socket_handle sock )
{
	closed_connections.push_back(sock);
}

void tcp_server::remove_connection( socket_handle sock )
{
	auto iter = std::find_if( begin(connections), end(connections), [=] ( auto& conn ) {
		return conn->handle() == sock;
	});
	if (iter == end(connections))
		return;

	mux.remove( sock );
	if (connections.size() > 1)
		std::iter_swap( iter, connections.end() - 1 );
	connections.pop_back();
}
} // namespace aw

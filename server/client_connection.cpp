#include <server/client_connection.h>
#include <server/number_parser.h>
#include <server/tcp_server.h>

namespace aw {
client_connection::client_connection(socket_tcp&& sock, tcp_server& server)
	: sock(std::move(sock)), server(server)
{
}

void client_connection::on_data_received()
{
	std::string msg;
	auto status = sock.receive( msg );
	if (status == socket_status::closed) {
		server.on_connection_closed( handle() );
		return;
	}

	auto response = generate_response( msg );

	sock.send( response );
}
} // namespace aw

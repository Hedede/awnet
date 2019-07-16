#pragma once
#include <server/data_callback.h>
#include <server/client_connection.h>
#include <shared/socket_tcp.h>

namespace aw {
struct tcp_server;
struct client_connection : data_callback {
	client_connection(socket_tcp&& sock, tcp_server& server);

	void on_data_received() override;

	socket_handle handle() { return sock.handle(); }

private:
	socket_tcp sock;
	tcp_server& server;
};

} // namespace aw

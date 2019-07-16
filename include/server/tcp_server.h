#pragma once
#include <server/data_callback.h>
#include <server/client_connection.h>
#include <server/socket_multiplexer.h>
#include <shared/socket_listener.h>
#include <vector>
#include <memory>

namespace aw {

struct tcp_server : data_callback {
	tcp_server(ip4_address addr, std::uint16_t port, multiplexer& mux);


	// TODO: redo this part
	void on_connection_closed( socket_handle sock );
	void cleanup_connections();

protected:
	void on_data_received() override;
	void create_connection( socket_tcp&& sock );

	void remove_connection(socket_handle);

private:
	std::vector<std::unique_ptr<client_connection>> connections;
	socket_listener sock;
	multiplexer& mux;
	std::vector<socket_handle> closed_connections;
};

} // namespace aw

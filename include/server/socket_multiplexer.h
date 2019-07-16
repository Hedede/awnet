#pragma once
#include <shared/socket_handle.h>

#include <server/data_callback.h>

#include <unordered_map>


namespace aw {
// TODO: make this into a template and move this into a separate header
struct handle_hash {
	auto operator()(socket_handle const& p) const noexcept
	{
		std::hash<int> hasher;
		return hasher( int(p) );
	}
};

struct multiplexer {
	void add(socket_handle handle, data_callback& callback);
	void remove(socket_handle handle);

	void select();

private:
	std::unordered_map<socket_handle, data_callback*, handle_hash> sockets;
	int max_fd;
};
} // namespace aw

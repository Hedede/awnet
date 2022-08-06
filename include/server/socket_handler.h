#pragma once
#include <functional>
#include <shared/socket_inet.h>

namespace aw {
struct socket_handler {

	void add(socket_handle handle, callback_type callback);
	void remove(socket_handle handle);

	void select();

private:
	// TODO: make this into a template and move this into a separate header
	struct handle_hash {
		auto operator()(socket_handle p) const noexcept
		{
			hash<int> hasher;
			return hasher( int(p) );
		}
	};

	std::unordered_map<socket_handle, std::reference_wrapper<callback_type>, handle_hash> sockets;
	int max_fd;
};
} // namespace aw

#include <server/socket_multiplexer.h>

#include <shared/error.h>

#include <algorithm>

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>

namespace aw {
void multiplexer::add(socket_handle handle, data_callback& callback)
{
	if (handle == invalid_socket_handle)
		return;
	sockets[handle] = &callback;
}

void multiplexer::remove(socket_handle handle)
{
	if (handle == invalid_socket_handle)
		return;
	sockets.erase(handle);
}

// TODO: this feels more complicated than it needs to be
void multiplexer::select()
{
	if (sockets.empty())
		return;

	int max_fd = -1;
	fd_set fds;
	FD_ZERO(&fds);

	for (auto [handle,_] : sockets) {
		auto fd = static_cast<int>(handle);
		FD_SET(fd, &fds);
		max_fd = std::max(max_fd, fd);
	}

	auto nready = ::select(max_fd+1, &fds, nullptr, nullptr, nullptr);
	if (nready == -1)
		throw_error("select");

	for (auto [handle,callback] : sockets) {
		auto fd = static_cast<int>(handle);
		if (FD_ISSET(fd, &fds))
			callback->notify_data_received();
	}
}
} // namespace aw

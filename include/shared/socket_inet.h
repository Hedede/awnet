#pragma once
#include <shared/address.h>
#include <shared/socket_handle.h>

namespace aw {
struct socket {
	socket(socket const&) = delete;
	socket(socket&& other)
		: fd(other.fd)
	{
		other.fd = -1;
	}

	socket& operator=(socket const&) = delete;
	socket& operator=(socket&& other)
	{
		fd = other.fd;
		other.fd = -1;
		return *this;
	}

	~socket();

	socket_handle handle() const;

	void close();

protected:
	socket(int fd)
		: fd(fd)
	{}

	socket(int type, ip4_address addr, std::uint16_t port);

	int get_fd() { return fd; }
	void make_non_blocking();

private:
	int fd;
};
} // namespace aw

#pragma once
#include <shared/address.h>
#include <shared/socket_handle.h>
#include <shared/protocols.h>

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


	void bind(ip4_address addr, std::uint16_t port);
	void connect(ip4_address addr, std::uint16_t port);

	void close();

protected:
	socket(int fd)
		: fd(fd)
	{}

	socket(protocol type);

	int get_fd() { return fd; }
	void make_non_blocking();
	void set_reuse_addr();

private:
	int fd;
};
} // namespace aw

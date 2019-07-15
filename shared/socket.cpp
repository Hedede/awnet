#include <shared/socket.h>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>

namespace aw {
[[noreturn]] static void throw_error(std::string where)
{
	throw std::runtime_error( where + ": " + strerror(errno) );
}

socket::socket(std::string name)
	: name{name}
{
	fd = ::socket(AF_UNIX, SOCK_STREAM, 0);
	if (fd == -1)
		throw_error("socket");

	// use aggregate initialization to zero-initialize the struct
	struct sockaddr_un sa {
		AF_UNIX
	};
	strncpy(sa.sun_path, name.data(), sizeof(sa.sun_path));

	int err = bind(fd, (struct sockaddr*)&sa, sizeof(sa));
	if (err == -1)
		throw_error("bind");
}


socket::~socket()
{
	close(data_socket);
	unlink(name.data());
}

void socket::listen(int backlog)
{
	int err = ::listen(fd, backlog);
	if (err == -1)
		throw_error("listen");
}

void socket::accept()
{
	if (data_socket != -1)
		close(data_socket);

	data_socket = ::accept(fd, nullptr, nullptr);
	if (data_socket == -1)
		throw_error("accept");
	std::cerr << "accepted " << data_socket << '\n';
}

std::string_view socket::receive()
{
	int ret = read(data_socket, buf, sizeof(buf));
	if (ret == -1)
		throw_error("read");
	return std::string_view{buf, unsigned(ret)};
}

void socket::send(std::string_view what)
{
	int err = write(data_socket, what.data(), what.size());
	if (err == -1)
		throw_error("write");
}
} // namespace aw

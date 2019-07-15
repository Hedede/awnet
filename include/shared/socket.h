#pragma once
#include <string>
#include <string_view>

struct socket {
	socket(std::string name);
	~socket();

	void listen(int backlog);
	void accept();

	std::string_view receive();
	void send(std::string_view what);

private:
	int fd;
	int data_socket = -1;
	std::string name;
	char buf[1024];
};

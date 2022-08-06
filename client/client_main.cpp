#include <shared/protocols.h>
#include <shared/address.h>

#include <iostream>

#include <stdio.h>
#include <unistd.h>


#include <shared/socket_tcp.h>
#include <shared/socket_udp.h>

int main(int argc, char** argv)
{
	if (argc < 3) {
		std::cerr << "USAGE: client ADDRESS PORT [PROTOCOL]\n";
		return EXIT_FAILURE;
	}

	aw::protocol protocol = aw::protocol::tcp;
	std::uint16_t port = 0;
	aw::ip4_address addr = 0;
	try {
		addr = aw::parse_address( argv[1] );
		port = aw::parse_port( argv[2] );
		if (argc >= 4) {
			using namespace std::string_literals;
			if (argv[3] == "udp"s || argv[3] == "UDP"s)
				protocol = aw::protocol::udp;
			else if (argv[3] == "tcp"s || argv[3] == "TCP"s)
				protocol = aw::protocol::tcp;
			else
				throw std::invalid_argument("Unknown protocol: "s + argv[3]);
		}
	} catch(std::exception& ex) {
		std::cerr << "error: " << ex.what() << '\n';
		return EXIT_FAILURE;
	}

	if (isatty(fileno(stdin)))
		std::cout << "Enter messages to be sent to the server. Each message is delimited by lines with words BEGIN and END. Anything between is ignored. Messages longer than 1024 characters are truncated.\n";
	

	auto read_message = [] {
		std::string message;
		std::string line;
		do {
			if (!std::getline(std::cin, line))
				break;
		} while (line != "BEGIN");
		while (line != "END") {
			if (!std::getline(std::cin, line))
				break;
			message += line;
			message += '\n';
		}
		return message;
	};

	if (protocol == aw::protocol::tcp) {
		aw::socket_tcp sock;
		sock.connect(addr, port);
		while (std::cin) {
			using namespace std::string_literals;
			auto message = read_message();
			if (message.size() > 1024) message.resize(1024);
			sock.send("BEGIN\0"s + message + "END\0"s);
			std::cout << '\n';
			std::cout << "MESSAGE\n" << message;
			if (!message.empty() && message.back() != '\n')
				std::cout << '\n';
			auto status = sock.receive(message);
			if (status == aw::socket_status::closed)
				break;
			std::cout << "RESPONSE\n" << message << "END\n\n";
		}
	} else {
		aw::socket_udp sock;
		while (std::cin) {
			auto message = read_message();
			if (message.size() > 1024) message.resize(1024);
			sock.send(message, addr, port);
			std::cout << '\n';
			std::cout << "MESSAGE\n" << message;
			if (!message.empty() && message.back() != '\n')
				std::cout << '\n';
			message = sock.receive(addr, port);
			std::cout << "RESPONSE\n" << message << "END\n\n";
		}
	}
}

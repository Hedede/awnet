#include <server/server.h>

#include <iostream>
#include <stdexcept>

#include <signal.h>


int main(int argc, char** argv)
{
	// TODO: I didn't have time to search for good options parser
	if (argc < 2) {
		std::cerr << "USAGE: server PORT [ADDRESS]\n";
		return EXIT_FAILURE;
	}

	std::uint16_t port = 0;
	aw::ip4_address addr = 0;
	try {
		port = aw::parse_port(argv[1]);
		if (argc >= 3)
			addr = aw::parse_address(argv[2]);
	} catch(std::exception& ex) {
		std::cerr << "error: " << ex.what() << '\n';
		return EXIT_FAILURE;
	}

	signal(SIGPIPE, SIG_IGN);

	try {
		aw::server srv(addr, port);
		srv.run();
	} catch( std::exception& ex ) {
		std::cerr << "Unrecoverable error occured:\n";
		std::cerr << ex.what() << '\n';
	}
}

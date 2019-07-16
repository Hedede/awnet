#include <server/server.h>

#include <thread>
#include <iostream>
#include <stdexcept>

#include <signal.h>

int main(int, char** argv)
{
	signal(SIGPIPE, SIG_IGN);
	
	try {
		aw::server srv(0, 10000);
		srv.run();
	} catch( std::exception& ex ) {
		std::cerr << "Unrecoverable error occured:\n";
		std::cerr << ex.what() << '\n';
	}
}

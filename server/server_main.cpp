#include <server/number_parser.h>
#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>

namespace aw {
template<typename T>
std::string join(std::vector<T> const& vec, char delimiter = ' ')
{
	auto size = vec.size();
	if (size == 0)
		return {};
	std::string s = std::to_string(vec[0]);
	for (size_t i = 1; i < size; ++i) {
		s += delimiter;
		s += std::to_string(vec[i]);
	}
	return s;
}

std::string generate_response(std::string const& message)
{
	auto numbers = parse_numbers(message);
	std::sort(numbers.begin(), numbers.end());
	auto sum = std::accumulate(numbers.begin(), numbers.end(), 0ull);

	auto response = join(numbers);
	response += '\n';
	response += std::to_string(sum);
	return response;
}
} // namespace aw


#include <shared/socket_listener.h>
#include <shared/socket_tcp.h>
#include <shared/socket_datagram.h>
#include <thread>

int main(int, char** argv)
{
	{
		aw::socket_listener sock(0, 10000, 32);

		auto conn = sock.accept();
		do {
			conn = sock.accept();
		} while(!conn);

		auto msg = conn->receive( );

		auto response = aw::generate_response( std::string(msg) );

		conn->send( response );
	}

	{
		aw::socket_datagram sock(0, 10000);

		aw::ip4_address addr;
		std::uint16_t port;

		auto msg = sock.receive( addr, port );

		auto response = aw::generate_response( std::string(msg) );

		sock.send( response, addr, port );
	}
}

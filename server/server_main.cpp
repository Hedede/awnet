#include <shared/socket.h>
#include <server/number_parser.h>
#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>

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

int main(int, char** argv)
{
	socket sock{"/tmp/test.socket"};

	sock.listen(1); // listen for 1 client
	sock.accept();

	auto msg = sock.receive();

	auto response = generate_response( std::string(msg) );

	sock.send( response );
}

#include <server/number_parser.h>

#include <numeric>
#include <algorithm>

namespace aw {
static const char numbers[] = "0123456789";
std::vector<unsigned long long> parse_numbers(std::string const& text)
{
	std::vector<unsigned long long> result;
	size_t pos_end = 0;
	do {
		auto pos_begin = text.find_first_of(numbers, pos_end);
		if (pos_begin == text.npos)
			break;

		pos_end = text.find_first_not_of(numbers, pos_begin);

		auto length = pos_end - pos_begin;
		auto number = std::stoull( text.substr( pos_begin, length ) );
		result.push_back( number );
	} while (true);
	return result;
}

// TODO: move it into a header
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
	try {
		auto numbers = parse_numbers(message);

		std::sort(numbers.begin(), numbers.end());
		auto sum = std::accumulate(numbers.begin(), numbers.end(), 0ull);

		auto response = join(numbers);
		response += '\n';
		response += std::to_string(sum);
		response += '\n';
		return response;
	} catch( std::out_of_range& ex ) {
		return "error:\nnumber is too large\n";
	}
}
	
} // namespace aw

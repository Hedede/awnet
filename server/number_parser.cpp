#include <server/number_parser.h>
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
} // namespace aw

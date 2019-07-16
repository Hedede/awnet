#pragma once
#include <vector>
#include <string>

namespace aw {
/*
 * Parses all numbers inside a string and ignores all other characters
 *
 * Example:
 * `parse_numbers("400 abc 200 zxc 300")`
 * will return
 * `{400, 200, 300}`
 */
std::vector<unsigned long long> parse_numbers(std::string const& text);

/*
 * Produces a message with return to the given message.
 * Responce consists of two lines: the first line contains
 * all numbers from the message in ascending order, the second
 * line contains their sum
 *
 * Example:
 * `parse_numbers("400 abc 200 zxc 300")`
 * will return
 * 200 300 400
 * 900
 */
std::string generate_response(std::string const& message);
} // namespace aw

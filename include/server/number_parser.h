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
} // namespace aw

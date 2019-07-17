#pragma once
#include <cstddef>
#include <cstdint>
#include <string>
namespace aw {
using ip4_address = std::uint32_t;
ip4_address parse_address(const char* str);
std::string address_string(ip4_address addr);

std::uint16_t parse_port(const char* str);
} //namespace aw

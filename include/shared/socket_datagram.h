#pragma once
#include <string>
#include <optional>
#include <string_view>
#include <shared/socket_inet.h>

namespace aw {
struct socket_datagram : socket {
	// \exceptions
	//    throws std::runtime_error if any error has occured
	socket_datagram(ip4_address addr, std::uint16_t port);

	// receive a message from the socket
	//
	// \param addr
	// \param port
	//    will be initialized with sender's address
	// \return
	//    string containing received message
	// \exceptions
	//    throws std::runtime_error if any error has occured
	std::string receive(ip4_address& addr, std::uint16_t& port);

	// same as receive, but non-blocking
	// \return
	//    nullopt is returned when socket is non-blocking and there was no data
	std::optional<std::string> receive_async(ip4_address& addr, std::uint16_t& port);

	// receive a message to a  socket
	//
	// \exceptions
	//    throws std::runtime_error if any error has occured
	void send(std::string_view, ip4_address addr, std::uint16_t port);
};
} // namespace aw

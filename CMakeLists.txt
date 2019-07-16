cmake_minimum_required(VERSION 3.14)
project(client)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(client client/client_main.cpp)
add_executable(server server/server_main.cpp server/number_parser.cpp server/socket_multiplexer.cpp server/server_tcp.cpp server/server_udp.cpp server/server.cpp server/client_connection.cpp server/data_callback.cpp)
add_library(common SHARED shared/socket.cpp shared/socket_datagram.cpp shared/socket_tcp.cpp shared/socket_listener.cpp)

target_compile_definitions(common PUBLIC lib)

target_link_libraries(client common)
target_link_libraries(server common)

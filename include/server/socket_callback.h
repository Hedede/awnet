#pragma once
#include <functional>

namespace aw {
struct socket;

using socket_callback_signature = void( socket& );
using socket_callback = std::function<socket_callback_signature>;

}

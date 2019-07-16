#include <server/data_callback.h>
#include <stdexcept>
#include <iostream>
namespace aw {
void data_callback::notify_data_received()
{
	try {
		on_data_received();
	} catch(std::exception& ex) {
		std::cerr << "error receiving data: " << ex.what() << '\n';
	}
}
} // namespace aw

#pragma once

namespace aw {

struct data_callback {
	//virtual data_callback() = default;
	
	void notify_data_received();

protected:
	virtual void on_data_received() = 0;
};

} // namespace aw

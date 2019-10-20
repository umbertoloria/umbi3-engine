#pragma once

class WindowCloseEvent : public Event {

public:

	const std::string getMessage () const {
		return "window closed";
	}

};
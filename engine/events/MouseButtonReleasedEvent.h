#pragma once

class MouseButtonReleasedEvent : public Event {

private:

	int button;

public:

	MouseButtonReleasedEvent (int button) : button(button) {}

	const std::string getMessage () const {
		return "{" + std::to_string(button) + " button released}";
	}

};
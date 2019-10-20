#pragma once

class MouseButtonPressedEvent : public Event {

private:

	int button;

public:

	MouseButtonPressedEvent (int button) : button(button) {}

	const std::string getMessage () const {
		return "{" + std::to_string(button) + " button pressed}";
	}

};
#pragma once

class KeyPressedEvent : public Event {

public:

	const int key;
	const bool pressing;

	KeyPressedEvent (int key, bool pressing) : key(key), pressing(pressing) {}

	const std::string getMessage () const {
		return "{" + std::to_string(key) + (pressing ? " pressing}" : " pressed}");
	}

};
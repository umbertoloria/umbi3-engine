#pragma once

class KeyPressedEvent : public Event {

private:

	int key;
	bool pressing;

public:

	KeyPressedEvent (int key, bool pressing) : key(key), pressing(pressing) {}

	const std::string getMessage () const {
		return "{" + std::to_string(key) + (pressing ? " pressing}" : " pressed}");
	}

};
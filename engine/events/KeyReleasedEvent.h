#pragma once

class KeyReleasedEvent : public Event {

public:

	const int key;

	KeyReleasedEvent (int key) : key(key) {}

	const std::string getMessage () const {
		return "{" + std::to_string(key) + " released}";
	}

};
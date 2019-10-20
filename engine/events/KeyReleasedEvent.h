#pragma once

class KeyReleasedEvent : public Event {

private:

	int key;

public:

	KeyReleasedEvent (int key) : key(key) {}

	const std::string getMessage () const {
		return "{" + std::to_string(key) + " released}";
	}

};
#pragma once

class WindowResizeEvent : public Event {

private:

	int width, height;

public:

	WindowResizeEvent (int width, int height) : width(width), height(height) {}

	const std::string getMessage () const {
		return "{" + std::to_string(width) + "/" + std::to_string(height) + "}";
	}

};
#pragma once

class MouseScrolledEvent : public Event {

private:

	float xOffset, yOffset;

public:

	MouseScrolledEvent (float xOffset, float yOffset) : xOffset(xOffset), yOffset(yOffset) {}

	const std::string getMessage () const {
		return "{" + std::to_string(xOffset) + "/" + std::to_string(yOffset) + " mouse new scroll offset}";
	}

};
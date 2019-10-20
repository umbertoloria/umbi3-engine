#pragma once

class MouseMovedEvent : public Event {

private:

	glm::vec2 position;

public:

	MouseMovedEvent (const glm::vec2& position) : position(position) {}

	const std::string getMessage () const {
		return "{" + std::to_string(position.x) + "/" + std::to_string(position.y) +
		       " mouse new position}";
	}

};
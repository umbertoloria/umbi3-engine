#pragma once

#include <glm/vec2.hpp>
#include <glm/glm.hpp>
#include "../engine/events/Event.h"
#include "../engine/events/KeyPressedEvent.h"
#include "../engine/events/KeyReleasedEvent.h"

class Controller2D {

private:

	int w, a, s, d;
	float speed;
	bool front{false}, back{false};
	bool left{false}, right{false};

public:

	Controller2D (int w, int a, int s, int d, float speed)
			: w(w), a(a), s(s), d(d), speed(speed) {}

	glm::vec2 calculateVec2 (float ts) {

		glm::vec2 v = {0.0f, 0.0f};

		if (left ^ right) {
			if (left) v.x--;
			if (right) v.x++;
		}

		if (front ^ back) {
			if (front) v.y++;
			if (back) v.y--;
		}

		if (glm::length(v) > 0) {
			v = glm::normalize(v) * glm::vec2(speed * ts, speed * ts);
		}

		return v;

	}

	void event (Event& event) {
		if (auto* v = dynamic_cast<KeyPressedEvent*>(&event)) {
			if (v->key == a) {
				left = true;
			} else if (v->key == d) {
				right = true;
			} else if (v->key == w) {
				front = true;
			} else if (v->key == s) {
				back = true;
			}
		} else if (auto* v = dynamic_cast<KeyReleasedEvent*>(&event)) {
			if (v->key == a) {
				left = false;
			} else if (v->key == d) {
				right = false;
			} else if (v->key == w) {
				front = false;
			} else if (v->key == s) {
				back = false;
			}
		}
	}

};
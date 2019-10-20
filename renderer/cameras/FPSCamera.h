#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

class FPSCamera : public Camera {

private:

	glm::vec3 position{0.0f};
	glm::vec2 rotation{0.0f};
	glm::mat4 matrix{1.0f};

	void updateMatrix () {
		matrix = glm::mat4{1.0};
		matrix = glm::translate(matrix, position);
		matrix = glm::rotate(matrix, glm::radians(rotation.y), {0, 1, 0});
		matrix = glm::rotate(matrix, glm::radians(rotation.x), {1, 0, 0});
		matrix = glm::inverse(matrix);
	}

public:

	inline const glm::vec3& getPosition () const { return position; }

	void setPosition (const glm::vec3& position) {
		FPSCamera::position = position;
		updateMatrix();
	}

	inline const glm::vec2& getRotation () const { return rotation; }

	void setRotation (const glm::vec2& rotation) {
		FPSCamera::rotation = rotation;
		updateMatrix();
	}

	inline const glm::mat4& getViewMatrix () const override { return matrix; };

};
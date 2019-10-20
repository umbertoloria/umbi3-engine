#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include "Projection.h"

class PerspectiveProjection : public Projection {

private:

	glm::mat4 matrix{1.0f};

public:

	explicit PerspectiveProjection (float fov, float aspect, float zNear, float zFar) {
		matrix = glm::perspective(glm::radians(fov), aspect, zNear, zFar);
	}

	inline const glm::mat4& getProjectionMatrix () const override { return matrix; }

};
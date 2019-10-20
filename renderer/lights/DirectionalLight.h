#pragma once

#include "Light.h"
#include "Attenuation.h"

class DirectionalLight : public Light {

private:

	glm::vec3 direction;

public:

	DirectionalLight (const Light& light, const glm::vec3& direction)
			: Light(light), direction(direction) {}

	const glm::vec3& getDirection () const {
		return direction;
	}

};
#pragma once

#include "Light.h"
#include "Attenuation.h"

class PointLight : public Light {

private:

	glm::vec3 position;
	Attenuation attenuation;

public:

	PointLight (const Light& light, const glm::vec3& position, const Attenuation& attenuation)
			: Light(light), position(position), attenuation(attenuation) {}

	const glm::vec3& getPosition () const {
		return position;
	}

	const Attenuation& getAttenuation () const {
		return attenuation;
	}

};
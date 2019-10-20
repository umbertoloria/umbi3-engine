#pragma once

class Light {

private:

	glm::vec3 ambient, diffuse, specular;

public:

	Light (const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
			: ambient(ambient), diffuse(diffuse), specular(specular) {}

	const glm::vec3& getAmbient () const {
		return ambient;
	}

	const glm::vec3& getDiffuse () const {
		return diffuse;
	}

	const glm::vec3& getSpecular () const {
		return specular;
	}

};
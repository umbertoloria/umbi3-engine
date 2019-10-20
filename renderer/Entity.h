#pragma once

#include <vector>
#include "Picture.h"
#include "lights/Light.h"

class Entity {

private:

	std::vector<Picture> pictures;
	glm::vec3 position{0.0f, 0.0f, 0.0f};
	glm::vec3 rotation{0.0f, .0f, 0.0f};
	glm::vec3 scale{1.0f};

public:

	Entity (const std::initializer_list<Picture>& pictures) : pictures(pictures) {}

	const glm::vec3& getPosition () const {
		return position;
	}

	void setPosition (const glm::vec3& position) {
		Entity::position = position;
	}

	const glm::vec3& getRotation () const {
		return rotation;
	}

	void setRotation (const glm::vec3& rotation) {
		Entity::rotation = rotation;
	}

	const glm::vec3& getScale () const {
		return scale;
	}

	void setScale (const glm::vec3& scale) {
		Entity::scale = scale;
	}

	void draw (const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix,
	           const glm::vec3& viewPosition,
	           const std::shared_ptr<DirectionalLight>& dirLight,
	           const std::shared_ptr<PointLight>& pointLight) {
		glm::mat4 transformation{1.0};
		transformation = glm::translate(transformation, position);
		transformation = glm::rotate(transformation, glm::radians(rotation.y), {0, 1, 0});
		transformation = glm::rotate(transformation, glm::radians(rotation.x), {1, 0, 0});
		transformation = glm::rotate(transformation, glm::radians(rotation.z), {0, 0, 1});
		transformation = glm::scale(transformation, scale);
		for (Picture& picture : pictures) {
			picture.draw(projectionMatrix, viewMatrix, transformation, viewPosition, dirLight, pointLight);
		}
	}

};
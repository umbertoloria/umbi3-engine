#pragma once

#include <memory>
#include <glm/gtc/matrix_transform.hpp>
#include "Renderer.h"

class Picture {

private:

	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<Shader> shader;

public:

	Picture (Mesh* mesh, std::shared_ptr<Shader>& shader)
			: mesh(mesh), shader(shader) {}

	void draw (const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix,
	           const glm::mat4& transformationMatrix, const glm::vec3& viewPosition,
	           const std::shared_ptr<DirectionalLight>& dirLight,
	           const std::shared_ptr<PointLight>& pointLight) {
		Renderer::commit(shader, mesh, projectionMatrix, viewMatrix, transformationMatrix,
		                 viewPosition, dirLight, pointLight);
	}

	virtual ~Picture () {
		mesh.reset();
		shader.reset();
	}

};
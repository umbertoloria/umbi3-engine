#pragma once

class Renderer {

public:

	static void commit (const std::shared_ptr<Shader>& shader, const std::shared_ptr<Mesh>& mesh,
	                    const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix,
	                    const glm::mat4& transformationMatrix) {
		shader->bind();
		shader->setUniformMat4f("projectionMatrix", projectionMatrix);
		shader->setUniformMat4f("viewMatrix", viewMatrix);
		shader->setUniformMat4f("transformationMatrix", transformationMatrix);
		mesh->draw();
	}

};
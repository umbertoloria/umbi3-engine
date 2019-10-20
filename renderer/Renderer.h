#pragma once

#include "lights/DirectionalLight.h"
#include "lights/PointLight.h"

class Renderer {

public:

	static void commit (const std::shared_ptr<Shader>& shader, const std::shared_ptr<Mesh>& mesh,
	                    const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix,
	                    const glm::mat4& transformationMatrix,
	                    const glm::vec3& viewPosition,
	                    const std::shared_ptr<DirectionalLight>& dirLight,
	                    const std::shared_ptr<PointLight>& pointLight) {
		shader->bind();
		shader->setUniformMat4f("projectionMatrix", projectionMatrix);
		shader->setUniformMat4f("viewMatrix", viewMatrix);
		shader->setUniformMat4f("transformationMatrix", transformationMatrix);
		shader->setUniform3f("viewPosition", viewPosition);
		if (dirLight) {
			// light
			shader->setUniform3f("dirLight.light.ambient", dirLight->getAmbient());
			shader->setUniform3f("dirLight.light.diffuse", dirLight->getDiffuse());
			shader->setUniform3f("dirLight.light.specular", dirLight->getSpecular());
			// directional light
			shader->setUniform3f("dirLight.direction", dirLight->getDirection());
			shader->setUniform1i("enableDirLight", 1);
		} else {
			shader->setUniform1i("enableDirLight", 0);
		}
		if (pointLight) {
			// light
			shader->setUniform3f("pointLight.light.ambient", pointLight->getAmbient());
			shader->setUniform3f("pointLight.light.diffuse", pointLight->getDiffuse());
			shader->setUniform3f("pointLight.light.specular", pointLight->getSpecular());
			// point light
			shader->setUniform3f("pointLight.position", pointLight->getPosition());
			// attenuation
			shader->setUniform1f("pointLight.attenuation.constant",
			                     pointLight->getAttenuation().constant);
			shader->setUniform1f("pointLight.attenuation.linear",
			                     pointLight->getAttenuation().linear);
			shader->setUniform1f("pointLight.attenuation.quadratic",
			                     pointLight->getAttenuation().quadratic);
			shader->setUniform1i("enablePointLight", 1);
		} else {
			shader->setUniform1i("enablePointLight", 0);
		}
		mesh->draw();
	}

};
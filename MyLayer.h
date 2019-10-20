#pragma once

#include <memory>
#include "engine/layers/Layer.h"
#include "engine/shaders/Shader.h"
#include "engine/mesh/Mesh.h"
#include "renderer/Entity.h"
#include "renderer/projections/PerspectiveProjection.h"
#include "renderer/cameras/FPSCamera.h"
#include "renderer/lights/Light.h"
#include "renderer/lights/DirectionalLight.h"
#include "renderer/lights/PointLight.h"
#include "utils/Controller2D.h"
#include <glm/gtx/rotate_vector.hpp>

class MyLayer : public Layer {

public:

	void attach () override {

		auto shader = std::make_shared<Shader>("shaders/vertex.glsl", "shaders/fragment.glsl");

		Picture p1(
				new Mesh(
						{
//                              POSITION              COLOR         NORMAL
								0.5f, 0.5f, 0,   /**/ 1, 1, 1, /**/ 0, 0, 1,
								-0.5f, 0.5f, 0,  /**/ 1, 1, 1, /**/ 0, 0, 1,
								-0.5f, -0.5f, 0, /**/ 1, 1, 1, /**/ 0, 0, 1,
								0.5f, -0.5f, 0,  /**/ 1, 1, 1, /**/ 0, 0, 1,
						},
						{0, 1, 2, 0, 2, 3},
						{Type::Float3, Type::Float3, Float3}
				),
				shader
		);

		Picture p2(
				new Mesh(
						{
//                              POSITION              COLOR               NORMAL
								0, 0.5f, 0,      /**/ 1, 1, 1,       /**/ 0, 0, 1,
								-0.5f, -0.5f, 0, /**/ 1, 0.3f, 0,    /**/ 0, 0, 1,
								0.5f, -0.5f, 0,  /**/ 0.2f, 0.2f, 1, /**/ 0, 0, 1,
						},
						{0, 1, 2},
						{Type::Float3, Type::Float3, Float3}
				),
				shader
		);

		plane.reset(new Entity({p1}));
		plane->setPosition({0, 0, -10});
		plane->setRotation({0, 45, 0});

		triangle.reset(new Entity({p2}));
		triangle->setPosition({0, 0, 0});

		/*dirLight.reset(new DirectionalLight(
				{
						{0.1f, 0.1f, 0.1f},
						{0, 1, 0},
						{1, 0, 0}
				},
				{0, 0, -1}
		));*/

		pointLight.reset(new PointLight(
				{
						{0.1f, 0.1f, 0.1f},
						{0, 1, 0},
						{0, 0, 1}
				},
				{0, 0, 0},
				{
					0, 0, 1
				}
		));

	}


private:

	std::shared_ptr<Entity> plane, triangle;
	PerspectiveProjection pers{45.0f, 16.0f / 9.0f, .0001f, 1000};
	FPSCamera camera;
	std::shared_ptr<DirectionalLight> dirLight;
	std::shared_ptr<PointLight> pointLight;
	Controller2D pos{GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_S, GLFW_KEY_D, 10};
	Controller2D rot{GLFW_KEY_UP, GLFW_KEY_LEFT, GLFW_KEY_DOWN, GLFW_KEY_RIGHT, 50};

public:

	void update (float ts) override {

		glm::vec2 rot2 = rot.calculateVec2(ts);
		glm::vec2 rot3 = {rot2.y, -rot2.x};
		camera.setRotation(camera.getRotation() + rot3);

		glm::vec2 pos2 = pos.calculateVec2(ts);
		glm::vec3 pos3 = {pos2.x, 0, -pos2.y};

		pos3 = glm::rotate(pos3, glm::radians(camera.getRotation().y), {0, 1, 0});
		camera.setPosition(camera.getPosition() + pos3);

//		plane->setRotation(
//				plane->getRotation() + glm::vec3(0, ts * 10, 0)
//		);

		plane->draw(pers.getProjectionMatrix(), camera.getViewMatrix(), camera.getPosition(),
		            dirLight, pointLight);
		triangle->draw(pers.getProjectionMatrix(), camera.getViewMatrix(), camera.getPosition(),
		               dirLight, pointLight);

	}

	void event (Event& event) override {
		pos.event(event);
		rot.event(event);
	}

	void detach () override {
		plane.reset();
	}

};
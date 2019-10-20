#pragma once

#include <memory>
#include "engine/layers/Layer.h"
#include "engine/shaders/Shader.h"
#include "engine/mesh/Mesh.h"
#include "renderer/Entity.h"
#include "renderer/projections/PerspectiveProjection.h"
#include "renderer/cameras/FPSCamera.h"

class MyLayer : public Layer {

private:

	std::shared_ptr<Entity> plane;

public:

	void attach () override {

		auto shader = std::make_shared<Shader>("shaders/vertex.glsl", "shaders/fragment.glsl");

		Picture p1(
				new Mesh(
						{
//                              POSITION              COLOR         NORMAL
								0.5f, 0.5f, 0,   /**/ 1, 0, 0, /**/ 0, 0, 1,
								-0.5f, 0.5f, 0,  /**/ 0, 1, 0, /**/ 0, 0, 1,
								-0.5f, -0.5f, 0, /**/ 0, 0, 0, /**/ 0, 0, 1,
								0.5f, -0.5f, 0,  /**/ 0, 0, 1, /**/ 0, 0, 1,
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

		plane = std::make_shared<Entity>(std::initializer_list<Picture>{p1, p2});
		plane->setPosition({0, 0, -10});

	}

	PerspectiveProjection pers{45.0f, 16.0f / 9.0f, .0001f, 1000};
	FPSCamera camera;

	void update (float timestep) override {

		camera.setPosition(
				camera.getPosition() - glm::vec3(0, 0, timestep)
		);

		plane->setRotation(
				plane->getRotation() + glm::vec3(0, timestep * 10, 0)
		);
		plane->draw(pers.getProjectionMatrix(), camera.getViewMatrix());
	}

	void detach () override {
		plane.reset();
	}

};
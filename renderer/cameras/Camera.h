#pragma once

class Camera {

public:

	virtual const glm::mat4& getViewMatrix () const = 0;

};
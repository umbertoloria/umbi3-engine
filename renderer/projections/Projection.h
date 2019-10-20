#pragma once

class Projection {

public:

	virtual const glm::mat4& getProjectionMatrix () const = 0;

};
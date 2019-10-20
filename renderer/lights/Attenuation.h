#pragma once

class Attenuation {

public:

	const float constant, linear, quadratic;

	Attenuation (float constant, float linear, float quadratic)
			: constant(constant), linear(linear), quadratic(quadratic) {}

};
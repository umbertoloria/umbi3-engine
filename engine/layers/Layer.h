#pragma once

class Layer {

public:

	virtual void attach () = 0;

	virtual void update (float timestep) = 0;

	virtual void detach () = 0;

};
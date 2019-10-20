#pragma once

class Layer {

public:

	virtual void attach () = 0;

	virtual void update (float ts) = 0;

	virtual void event (Event& event) = 0;

	virtual void detach () = 0;

};
#pragma once

#include <vector>
#include <iostream>
#include "Layer.h"

class LayerStack {

private:

	std::vector<Layer*> layers;
	// TODO: I layer vengono distriutti quando distruggo LayerStack?

public:

	void add (Layer* layer) {
		layers.push_back(layer);
	}

	void attach () {
		for (auto layer : layers) {
			layer->attach();
		}
	}

	void update (float timestep) {
		for (auto layer : layers) {
			layer->update(timestep);
		}
	}

	void event (Event& event) {
		// TODO: Ordine inverso
		for (auto layer : layers) {
			layer->event(event);
		}
	}

	void detach () {
		for (auto layer : layers) {
			layer->detach();
		}
	}
};
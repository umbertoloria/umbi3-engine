#pragma once

#include <memory>
#include "Window.h"
#include "layers/Layer.h"
#include "layers/LayerStack.h"
#include "../platform/windows/WindowsWindow.h"

class App {

private:

	std::unique_ptr<Window> window;
	LayerStack layerStack;

public:


	App (const std::string& title, int width, float aspectRatio) {
		WindowProps windowProps(title, width, aspectRatio);
		window = std::make_unique<WindowsWindow>(windowProps);

		window->setAntialiasing(true);
		window->setEventCallback(std::bind(&App::newEvent, this, std::placeholders::_1));
	}

	void newEvent (Event& e) {
//		std::cout << e.getMessage() << "\n";
		// TODO: Propagare "e" a tutti i layer.
	}

	void add (Layer* layer) {
		layerStack.add(layer);
	}

	void run () {
		while (window->getTime() <= 0.12) {
			window->update();
		}
		float lastFrameTime = window->getTime();
		int fps = 0;
		float lastFPSCheck = lastFrameTime;
		layerStack.attach();
		while (!window->shouldClose()) {
			window->clear();
			float time = window->getTime();
			float timestep = time - lastFrameTime;
			lastFrameTime = time;
			layerStack.update(timestep);
			window->update();
			fps++;
			if (lastFPSCheck + 1 <= lastFrameTime) {
				window->setTitle("FPS: " + std::to_string(fps));
				fps = 0;
				lastFPSCheck = time;
			}
		}
		layerStack.detach();
//		window->destroy();
	}

};
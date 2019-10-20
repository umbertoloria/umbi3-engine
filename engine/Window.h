#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <functional>
#include <glm/vec3.hpp>
#include "events/Event.h"

struct WindowProps {

	const std::string title;
	const int width, height;

	WindowProps (const std::string& title, int width, int height)
			: title(title), width(width), height(height) {}

	WindowProps (const std::string& title, int width, float aspectRatio)
			: title(title), width(width), height((int) (width / aspectRatio)) {}
};

class Window {

private:

	using EventCallbackFn = std::function<void (Event&)>;

protected:

	EventCallbackFn eventCallback;

public:

	inline void setEventCallback (const EventCallbackFn& callback) { eventCallback = callback; }

	virtual bool shouldClose () = 0;

	virtual void terminate () = 0;

	virtual ~Window () = default;

	// RENDERING

	virtual void setClearColor (const glm::vec3& color) = 0;

	virtual void clear () = 0;

	virtual void update () = 0;

	virtual float getTime () = 0;

	// OPTIONS

	virtual bool isVSYnc () const = 0;

	virtual void setVSync (bool enabled) = 0;

	virtual void setAntialiasing (bool enabled) = 0;

	virtual void setWireframeMode (bool status) = 0;

	virtual void setTitle (const std::string& title) = 0;

};

/*
class Window {

	// OPTIONS

	void setCursorCatched (bool status) {
		glfwSetInputMode(window, GLFW_CURSOR, status ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
	}

};
 */
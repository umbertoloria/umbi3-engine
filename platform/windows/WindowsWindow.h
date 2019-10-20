#pragma once

#include <iostream>
#include <glm/vec2.hpp>
#include "../../engine/events/KeyPressedEvent.h"
#include "../../engine/events/KeyReleasedEvent.h"
#include "../../engine/events/MouseButtonPressedEvent.h"
#include "../../engine/events/MouseButtonReleasedEvent.h"
#include "../../engine/events/MouseMovedEvent.h"
#include "../../engine/events/MouseScrolledEvent.h"
#include "../../engine/events/WindowCloseEvent.h"
#include "../../engine/events/WindowResizeEvent.h"

class WindowsWindow : public Window {

private:

	GLFWwindow* window;
	std::string title;
	int width, height;
	bool fullscreen{false};
	bool vsync{false};

public:

	explicit WindowsWindow (const WindowProps& props)
			: title(props.title), width(props.width), height(props.height) {
		glfwInit();
		glfwDefaultWindowHints();
		window = glfwCreateWindow(width, height, title.c_str(),
		                          fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
		glfwMakeContextCurrent(window);
		gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

		glEnable(GL_DEPTH_TEST);

		glfwSetWindowUserPointer(window, this);
		glfwSetWindowSizeCallback(window, [] (GLFWwindow* _window, int _width, int _height) {
			WindowsWindow& data = *(WindowsWindow*) glfwGetWindowUserPointer(_window);
			data.width = _width;
			data.height = _height;

			WindowResizeEvent event(_width, _height);
			data.eventCallback(event);

		});

		glfwSetWindowCloseCallback(window, [] (GLFWwindow* _window) {
			WindowsWindow& data = *(WindowsWindow*) glfwGetWindowUserPointer(_window);
			WindowCloseEvent event;
			data.eventCallback(event);
		});

		// FIXME: sync con umbi2-engine

		glfwSetKeyCallback(window,
		                   [] (GLFWwindow* _window, int key, int scancode, int action, int mods) {
			                   WindowsWindow& data = *(WindowsWindow*) glfwGetWindowUserPointer(
					                   _window);

			                   switch (action) {
				                   case GLFW_PRESS: {
					                   KeyPressedEvent event(key, false);
					                   data.eventCallback(event);
					                   break;
				                   }
				                   case GLFW_RELEASE: {
					                   KeyReleasedEvent event(key);
					                   data.eventCallback(event);
					                   break;
				                   }
				                   case GLFW_REPEAT: {
					                   KeyPressedEvent event(key, true);
					                   data.eventCallback(event);
					                   break;
				                   }
			                   }
		                   });
/*
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(keycode);
			data.EventCallback(event);
		});
*/
		glfwSetMouseButtonCallback(window,
		                           [] (GLFWwindow* _window, int button, int action, int mods) {
			                           WindowsWindow& data = *(WindowsWindow*) glfwGetWindowUserPointer(
					                           _window);

			                           switch (action) {
				                           case GLFW_PRESS: {
					                           MouseButtonPressedEvent event(button);
					                           data.eventCallback(event);
					                           break;
				                           }
				                           case GLFW_RELEASE: {
					                           MouseButtonReleasedEvent event(button);
					                           data.eventCallback(event);
					                           break;
				                           }
			                           }
		                           });

		glfwSetScrollCallback(window, [] (GLFWwindow* _window, double xOffset, double yOffset) {
			WindowsWindow& data = *(WindowsWindow*) glfwGetWindowUserPointer(_window);

			MouseScrolledEvent event((float) xOffset, (float) yOffset);
			data.eventCallback(event);
		});

		glfwSetCursorPosCallback(window, [] (GLFWwindow* _window, double xPos, double yPos) {
			WindowsWindow& data = *(WindowsWindow*) glfwGetWindowUserPointer(_window);

			MouseMovedEvent event (glm::vec2((float) xPos, (float) yPos));
			data.eventCallback(event);
		});
	}

	bool shouldClose () override {
		return glfwWindowShouldClose(window);
	}

	void terminate () override {
		glfwSetWindowShouldClose(window, true);
	}

	~WindowsWindow () override {
		glfwTerminate();
		window = nullptr;
	}

	// RENDERING

	void setClearColor (const glm::vec3& color) override {
		glClearColor(color.r, color.g, color.b, 1);
	}

	void clear () override {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void update () override {
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	float getTime () override {
		return (float) glfwGetTime();
	}

	// OPTIONS

	inline bool isVSYnc () const override { return vsync; }

	void setVSync (bool enabled) override {
		glfwSwapInterval(enabled ? 1 : 0);
		vsync = enabled;
	}

	void setAntialiasing (bool enabled) override {
		if (enabled)
			glEnable(GL_MULTISAMPLE);
		else
			glDisable(GL_MULTISAMPLE);
	}

	void setWireframeMode (bool status) override {
		glPolygonMode(GL_FRONT_AND_BACK, status ? GL_LINE : GL_FILL);
	}

	void setTitle (const std::string& title) override {
		WindowsWindow::title = title;
		glfwSetWindowTitle(window, WindowsWindow::title.c_str());
	}


};

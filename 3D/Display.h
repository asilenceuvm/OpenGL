#pragma once

#include <iostream>
#include <GLFW/glfw3.h>

class Display {
public:
	Display(int width, int height) {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);
		if (window == NULL) {
			std::cout << "Failed to create window" << std::endl;
			glfwTerminate();
		}

		glfwMakeContextCurrent(window);
		glViewport(0, 0, 800, 600);
	}
	~Display() {

	}

	GLFWwindow* getWindow() {
		return window;
	}
private:
	GLFWwindow* window;
};
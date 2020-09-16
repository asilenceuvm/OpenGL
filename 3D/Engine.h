#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Display.h"
#include "Game.h"
#include "InputManager.h"
#include "Logger.h"

class Engine {
public:
	Engine();
	~Engine();

	void update();
	void render();

	void run(double delta);
private:
	int width, height;

	GLFWwindow* window;
	Game* game;
};


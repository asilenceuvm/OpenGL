#include "Engine.h"
#include "Engine.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Display.h"
#include "Game.h"
#include "InputManager.h"

GLFWwindow* window;
Game* game;


Engine::Engine() {
	width = 800;
	height = 600;
	Display display = Display(width, height);
	window = display.getWindow();

	glewInit();

	//global gl settings
	//depth buffer
	glEnable(GL_DEPTH_TEST);
	//alpha channel
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//face culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);
	//Anti Aliasing
	glfwWindowHint(GLFW_SAMPLES, 4); //4x MSAA
	glEnable(GL_MULTISAMPLE);
	//vsync
	//glfwSwapInterval(1); //vsync
	glfwSwapInterval(0); //not vsync
	//print graphics context
	std::cout << glGetString(GL_RENDERER) << std::endl;

	glfwSetKeyCallback(window, InputManager::key_callback);

	InputManager::lastX = static_cast<float>(width / 2);
	InputManager::lastY = static_cast<float>(height / 2);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, InputManager::mouse_callback);

	game = new Game(width, height);
}

Engine::~Engine() {
	delete game;
	glfwTerminate();
}

void Engine::update() {
	game->update();
	//temp kill button
	if (InputManager::keys[GLFW_KEY_ESCAPE]) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void Engine::render() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//draw
	game->render();
	//end draw

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Engine::run(double delta) {
	double lastTime = glfwGetTime(), timer = lastTime;
	double deltaTime = 0, nowTime = 0;
	int frames = 0, updates = 0;

	//enter loop
	while (!glfwWindowShouldClose(window)) {

		//get time
		nowTime = glfwGetTime();
		deltaTime += (nowTime - lastTime) / delta;
		lastTime = nowTime;

		//update at delta
		while (deltaTime >= 1.0) {
			update();
			updates++;
			deltaTime--;
		}

		render();
		frames++;

		//reset and output fps
		if (glfwGetTime() - timer > 1.0) {
			timer++;
			std::cout << "FPS: " << frames << " Updates:" << updates << std::endl;
			updates = 0, frames = 0;
		}

	}
}
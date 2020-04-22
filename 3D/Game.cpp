#include "Game.h"

#include "Camera.h"
#include "ResourceManager.h"
#include "InputManager.h"

#include <iostream>

glm::mat4 view(1);
Camera camera;

Game::Game(int width, int height) {
	this->width = width;
	this->height = height;
	init();
}


Game::~Game() {
	delete renderer;
}


void Game::render() {
	renderer->drawSprite(ResourceManager::getTexture("background"), glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-55.0f, 0.0f, 0.0f));
	renderer->drawSprite(ResourceManager::getTexture("background"), glm::vec3(2.0f, 0.0f, -5.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 10.0f));
}

void Game::update() {
	if (InputManager::keys[GLFW_KEY_W]) {
		camera.moveCamForward(0.05f);
	}
	if (InputManager::keys[GLFW_KEY_S]) {
		camera.moveCamBack(0.05f);
	}
	if (InputManager::keys[GLFW_KEY_A]) {
		camera.moveCamLeft(0.05f);
	}
	if (InputManager::keys[GLFW_KEY_D]) {
		camera.moveCamRight(0.05f);
	}
	camera.rotateCamera(InputManager::xoffset, InputManager::yoffset, 0.1f);
	InputManager::xoffset = 0;
	InputManager::yoffset = 0;
	//std::cout << InputManager::xoffset << std::endl;
	//std::cout << InputManager::yoffset << std::endl;
	glm::vec3 cameraPos = camera.getCameraPos();
	glm::vec3 cameraFront = camera.getCameraFront();
	glm::vec3 cameraUp = camera.getCameraUp();
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	ResourceManager::getShader("basic").setMat4("view", view);
}


void Game::init() {
	ResourceManager::loadShader("res/shaders/basic.vs", "res/shaders/basic.fs", nullptr, "basic");
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<GLfloat>(width / height), 0.1f, 100.0f);
	ResourceManager::getShader("basic").use().setInt("image", 0);
	ResourceManager::getShader("basic").setMat4("projection", projection);
	ResourceManager::loadTexture("res/textures/person.png", GL_TRUE, "person");
	ResourceManager::loadTexture("res/textures/tree.png", GL_TRUE, "tree");
	ResourceManager::loadTexture("res/textures/background.png", GL_FALSE, "background");
	ResourceManager::loadTexture("res/textures/grass.png", GL_TRUE, "grass");
	Shader shader = ResourceManager::getShader("basic");
	renderer = new Renderer(shader);
}
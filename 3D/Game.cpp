#include "Game.h"

#include "Camera.h"
#include "ResourceManager.h"
#include "InputManager.h"

#include <iostream>
#include "Plane.h"

glm::mat4 view(1);
Camera camera;
Plane* plane;
Plane* plane2;
float x,y;

Game::Game(int width, int height) {
	this->width = width;
	this->height = height;
	init();

	plane = new Plane("background", glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-55.0f, 0.0f, 0.0f));
	plane2 = new Plane("background", glm::vec3(2.0f, 0.0f, -5.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 10.0f));
}


Game::~Game() {
	delete plane;
	delete plane2;
	delete renderer;
}


void Game::render() {
	plane->render(renderer);
	plane2->render(renderer);
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
	glm::vec3 cameraPos = camera.getCameraPos();
	glm::vec3 cameraFront = camera.getCameraFront();
	glm::vec3 cameraUp = camera.getCameraUp();
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	ResourceManager::getShader("lighted").setMat4("view", view);
	ResourceManager::getShader("lighted").setVec3("viewPos", cameraPos);
	x += 0.01f;
	y += 0.01f;
	ResourceManager::getShader("lighted").setVec3("lightPos", glm::vec3(0.0f, 2.0f, cos(x) - 3.0));
}


void Game::init() {
	ResourceManager::loadShader("res/shaders/lighted.vs", "res/shaders/lighted.fs", nullptr, "lighted");
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<GLfloat>(width / height), 0.1f, 100.0f);
	ResourceManager::getShader("lighted").use().setInt("image", 0);
	ResourceManager::getShader("lighted").setMat4("projection", projection);
	ResourceManager::getShader("lighted").setFloat("ambientStrength", 0.3f);
	ResourceManager::getShader("lighted").setVec3("objectColor", 0.2f, 0.8f, 0.8f);
	ResourceManager::getShader("lighted").setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	ResourceManager::getShader("lighted").setVec3("lightPos", glm::vec3(0.0f, 2.0f, -3.0f));
	ResourceManager::loadTexture("res/textures/person.png", GL_TRUE, "person");
	ResourceManager::loadTexture("res/textures/tree.png", GL_TRUE, "tree");
	ResourceManager::loadTexture("res/textures/background.png", GL_FALSE, "background");
	ResourceManager::loadTexture("res/textures/grass.png", GL_TRUE, "grass");
	Shader shader = ResourceManager::getShader("lighted");
	renderer = new Renderer(shader);
}
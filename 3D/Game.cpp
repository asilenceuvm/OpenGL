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
Plane* plane3;

Game::Game(int width, int height) {
	this->width = width;
	this->height = height;
	init();

	plane = new Plane("crate", "crateSpecular", glm::vec3(0.0f, 0.0f, -2.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(90.0f, 0.0f, 0.0f));
	plane3 = new Plane("crate", "crateSpecular", glm::vec3(0.0f, 0.25f, -2.75f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 0.0f));
	plane2 = new Plane("light", "light", glm::vec3(0.0f, 1.0f, -3.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 0.0f, 10.0f));
}


Game::~Game() {
	delete plane;
	delete plane2;
	delete plane3;
	delete renderer;
}


void Game::render() {
	plane->render(renderer);
	plane2->render(renderer);
	plane3->render(renderer);
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
//	plane->setRotate(glm::vec3(glfwGetTime() * 20, 0, 0));

//	ResourceManager::getShader("lighted").setVec3("dirLight.direction", 0.0f, 3 * cos(glfwGetTime()), 3 * sin(glfwGetTime()));
}


void Game::init() {
	ResourceManager::loadShader("res/shaders/lighted.vs", "res/shaders/lighted.fs", nullptr, "lighted");

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<GLfloat>(width / height), 0.1f, 100.0f);
	ResourceManager::getShader("lighted").use().setInt("image", 0);
	ResourceManager::getShader("lighted").setMat4("projection", projection);

	ResourceManager::getShader("lighted").setInt("material.diffuse", 0);
	ResourceManager::getShader("lighted").setInt("material.specular", 1);
	ResourceManager::getShader("lighted").setFloat("material.shine", 64.0f);
	
	ResourceManager::getShader("lighted").setVec3("dirLight.direction", 0.0f, 0.0f, -1.0f);
	ResourceManager::getShader("lighted").setVec3("dirLight.ambient", 0.2f, 0.2f, 0.2f);
	ResourceManager::getShader("lighted").setVec3("dirLight.diffuse", 0.5f, 0.5f, 0.5f);
	ResourceManager::getShader("lighted").setVec3("dirLight.specular", 1.0f, 1.0f, 1.0f);

	ResourceManager::getShader("lighted").setVec3("pointLight.position", 0.0f, 0.0f, -3.0f);
	ResourceManager::getShader("lighted").setFloat("pointLight.constant", 1.0f);
	ResourceManager::getShader("lighted").setFloat("pointLight.linear", 0.09f);
	ResourceManager::getShader("lighted").setFloat("pointLight.quadratic", 0.032f);
	ResourceManager::getShader("lighted").setVec3("pointLight.ambient", 0.2f, 0.2f, 0.2f);
	ResourceManager::getShader("lighted").setVec3("pointLight.diffuse", 0.5f, 0.5f, 0.5f);
	ResourceManager::getShader("lighted").setVec3("pointLight.specular", 1.0f, 1.0f, 1.0f);

	ResourceManager::getShader("lighted").setVec3("objectColor", 0.8f, 0.8f, 0.8f);
	ResourceManager::getShader("lighted").setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	ResourceManager::getShader("lighted").setVec3("lightPos", 0.0f, 1.0f, -3.0f);

	ResourceManager::loadTexture("res/textures/person.png", GL_TRUE, "person");
	ResourceManager::loadTexture("res/textures/tree.png", GL_TRUE, "tree");
	ResourceManager::loadTexture("res/textures/background.png", GL_FALSE, "background");
	ResourceManager::loadTexture("res/textures/crate.png", GL_TRUE, "crate");
	ResourceManager::loadTexture("res/textures/crateSpecular.png", GL_TRUE, "crateSpecular");
	ResourceManager::loadTexture("res/textures/grass.png", GL_TRUE, "grass");

	Shader shader = ResourceManager::getShader("lighted");
	renderer = new Renderer(shader);
}
#include "Game.h"

#include <GLFW/glfw3.h>

#include <iostream>

#include "Logger.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "Plane.h"
#include "ObjectManager.h"
#include "Model.h"

glm::mat4 view(1);
Camera camera;
ObjectRenderer* objectRenderer;
WaterRenderer* waterRenderer;
ModelRenderer* modelRenderer;
ObjectManager objectManager;
Model* model;

float x = 0.0f;

Game::Game(int width, int height) {
	this->width = width;
	this->height = height;
	init();

	objectManager.addPlane(Plane("crate", "crateSpecular", glm::vec3(0.0f, 0.0f, -2.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(90.0f, 0.0f, 0.0f)));
	objectManager.addPlane(Plane("crate", "crateSpecular", glm::vec3(0.0f, 0.25f, -2.75f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 0.0f)));

	//starting values for camera
	InputManager::xoffset = 0;
	InputManager::yoffset = 0;
	camera.rotateCamera(-90, 0, 1);
}


Game::~Game() {
	delete objectRenderer;
	delete waterRenderer;
	delete model;
}


void Game::render() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//objectManager.render(objectRenderer);
	modelRenderer->render(model, glm::vec3(0, 0, -5), glm::vec3(1, 1, 1), glm::vec3(0, 0, 5 * sin(glfwGetTime())));
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
	
	ResourceManager::getShader("lighted").use();
	ResourceManager::getShader("lighted").setVec3("pointLight.position", 2 * sin(x), 2 * cos(x), -2.0f);
	x -= 0.01f;
  	ResourceManager::getShader("lighted").setMat4("view", view);
	ResourceManager::getShader("lighted").setVec3("viewPos", cameraPos);

	ResourceManager::getShader("water").use();
	ResourceManager::getShader("water").setMat4("view", view);
	ResourceManager::getShader("water").setFloat("time", glfwGetTime());

	objectManager.update();

	//temp
	if (InputManager::keys[GLFW_KEY_F]) {
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	}

	if (InputManager::keys[GLFW_KEY_V]) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}


}


void Game::init() {
	Logger::logMessage("RES", "Generating Resources");
	//lighted shader
	ResourceManager::loadShader("res/shaders/lighted.vert", "res/shaders/lighted.frag", nullptr, "lighted");

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<GLfloat>(width / height), 0.1f, 100.0f);
	
	ResourceManager::getShader("lighted").use().setInt("image", 0);
	ResourceManager::getShader("lighted").setMat4("projection", projection);

	ResourceManager::getShader("lighted").setInt("material.diffuse", 0);
	ResourceManager::getShader("lighted").setInt("material.specular", 1);
	ResourceManager::getShader("lighted").setFloat("material.shine", 64.0f);
	
	ResourceManager::getShader("lighted").setVec3("dirLight.direction", 0.0f, -0.0f, -1.0f);
	ResourceManager::getShader("lighted").setVec3("dirLight.ambient", 0.2f, 0.2f, 0.2f);
	ResourceManager::getShader("lighted").setVec3("dirLight.diffuse", 0.5f, 0.5f, 0.5f);
	ResourceManager::getShader("lighted").setVec3("dirLight.specular", 0.3f, 0.3f, 0.3f);

	ResourceManager::getShader("lighted").setVec3("pointLight.position", 0.0f, 1.0f, -2.0f);
	ResourceManager::getShader("lighted").setFloat("pointLight.constant", 1.0f);
	ResourceManager::getShader("lighted").setFloat("pointLight.linear", 0.09f);
	ResourceManager::getShader("lighted").setFloat("pointLight.quadratic", 0.032f);
	ResourceManager::getShader("lighted").setVec3("pointLight.ambient", 0.2f, 0.2f, 0.2f);
	ResourceManager::getShader("lighted").setVec3("pointLight.diffuse", 0.5f, 0.5f, 0.5f);
	ResourceManager::getShader("lighted").setVec3("pointLight.specular", 1.0f, 1.0f, 1.0f);

	ResourceManager::getShader("lighted").setVec3("objectColor", 0.8f, 0.8f, 0.8f);
	ResourceManager::getShader("lighted").setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	ResourceManager::getShader("lighted").setVec3("lightPos", 0.0f, 1.0f, -3.0f);

	Shader shader = ResourceManager::getShader("lighted");
	objectRenderer = new ObjectRenderer(shader);


	//water shader
	ResourceManager::loadShader("res/shaders/water.vert", "res/shaders/water.frag", nullptr, "water");
	ResourceManager::getShader("water").use();
	ResourceManager::getShader("water").setInt("screenTexture", 0);
	ResourceManager::getShader("water").setMat4("projection", projection);

	Shader wshader = ResourceManager::getShader("water");
	waterRenderer = new WaterRenderer(wshader);


	//models
	stbi_set_flip_vertically_on_load(true);
	model = new Model("res/models/backpack/backpack.obj");

	modelRenderer = new ModelRenderer(shader);


	//textures
	ResourceManager::loadTexture("res/textures/person.png", GL_TRUE, "person");
	ResourceManager::loadTexture("res/textures/tree.png", GL_TRUE, "tree");
	ResourceManager::loadTexture("res/textures/crate.png", GL_TRUE, "crate");
	ResourceManager::loadTexture("res/textures/crateSpecular.png", GL_FALSE, "crateSpecular");
	
	Logger::logSuccess("RES", "Successfully loaded resources");
}
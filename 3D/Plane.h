#pragma once
#include "Renderer.h"
#include "ResourceManager.h"

class Plane {
public:
	Plane(std::string texture, glm::vec3 position, glm::vec3 scale, glm::vec3 rotate) {
		this->texture = texture;
		this->position = position;
		this->scale = scale;
		this->rotate = rotate;
	}

	void update() {

	}
	
	void render(Renderer* renderer) {
		renderer->drawSprite(ResourceManager::getTexture(texture), position, scale, rotate);
	}
private:
	std::string texture;
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotate;
};

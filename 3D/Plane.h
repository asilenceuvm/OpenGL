#pragma once
#include "Renderer.h"
#include "ResourceManager.h"

class Plane {
public:
	Plane(std::string texture, std::string spec, glm::vec3 position, glm::vec3 scale, glm::vec3 rotate) {
		this->texture = texture;
		this->spec = spec;
		this->position = position;
		this->scale = scale;
		this->rotate = rotate;
	}

	void update() {

	}
	
	void render(Renderer* renderer) {
		renderer->drawSprite(ResourceManager::getTexture(texture), ResourceManager::getTexture(spec), position, scale, rotate);
	}

	void setRotate(glm::vec3 rotate) {
		this->rotate = rotate;
	}

private:
	std::string texture, spec;
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotate;
};

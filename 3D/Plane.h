#pragma once

#include <memory>

#include "Renderers.h"
#include "ResourceManager.h"
#include "Rigidbody.h"

class Plane {
public:
	Plane(std::string texture, std::string spec, glm::vec3 position, glm::vec3 scale, glm::vec3 rotate) : body(position, glm::vec3(0)) {
		this->texture = texture;
		this->spec = spec;
		this->position = position;
		this->scale = scale;
		this->rotate = rotate;
	}

	void update() {
		body.update();
		//position = body.getPos();
	}
	
	void render(ObjectRenderer* renderer) {
		renderer->drawObject(ResourceManager::getTexture(texture), ResourceManager::getTexture(spec), position, scale, rotate);
	}

	void setRotate(glm::vec3 rotate) {
		this->rotate = rotate;
	}

private:
	std::string texture, spec;
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotate;

	RigidBody body;
};

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class RigidBody {
public:
	RigidBody(glm::vec3 position, glm::vec3 velocity) {
		this->position = position;
		this->velocity = velocity;
		this->acceleration = glm::vec3(0, -0.001f, 0);
	}

	void update() {
		velocity += acceleration;
		position += velocity;
	}

	glm::vec3 getPos() {
		return position;
	}


private:
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;
};

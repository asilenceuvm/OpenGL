#include "ObjectManager.h"

void ObjectManager::update() {
	for (auto& plane : planes) {
		plane.update();
	}
}

void ObjectManager::render(ObjectRenderer* renderer) {
	for (auto& plane : planes) {
		plane.render(renderer);
	}
}

void ObjectManager::addPlane(Plane plane) {
	planes.push_back(plane);
}

void ObjectManager::clearPlanes() {
	planes.clear();
}
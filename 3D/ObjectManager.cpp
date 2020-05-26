#include "ObjectManager.h"

void ObjectManager::update()
{
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
	for (auto& plane : planes) {

	}
}

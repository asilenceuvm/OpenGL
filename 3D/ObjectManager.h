#pragma once
#include "Renderers.h"
#include "Plane.h"

#include <vector>

class ObjectManager {
public:
	void update();
	void render(ObjectRenderer* renderer);

	void addPlane(Plane plane);

	void clearPlanes();
private:
	std::vector<Plane> planes;
};


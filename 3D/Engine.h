#pragma once

#include "Logger.h"

class Engine {
public:
	Engine();
	~Engine();

	void update();
	void render();

	void run(double delta);
private:
	int width, height;
};


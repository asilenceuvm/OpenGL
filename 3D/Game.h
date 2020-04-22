#pragma once

#include "Renderer.h"

class Game {
public:
	Game(int width, int height);
	~Game();
	void render();
	void update();
private:
	Renderer* renderer;
	int width, height;
	void init();
};


#pragma once

#include "Renderers.h"

class Game {
public:
	Game(int width, int height);
	~Game();
	void render();
	void update();
private:
	int width, height;
	void init();
};


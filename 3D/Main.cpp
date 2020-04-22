#include "Engine.h"

int main() {
	Engine engine = Engine();
	engine.run(1.0 / 60.0); //60 updates per second

	return 0;
}
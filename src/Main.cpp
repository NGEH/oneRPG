
#define SDL_MAIN_HANDLED

#include <cstdio>

#include <SDL.h>
#include "Renderer.h"
#include "EventManager.h"

Renderer renderer;
EventManager event_manager;

void ExitGame(void*) {
	exit(-1);
}

int x = 0;
int y = 0;

int main() {

	bool running = true;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("win", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

	// Initialize modules
	renderer.initialise(window);
	event_manager.initialise();

	event_manager.register_subscriber("InputExit", ExitGame);

	// @Temporary: create an event manager to deal with these
	SDL_Event e;

	while (running) {
		char str[32];
		sprintf_s(str, "%d, %d", x, y);
		SDL_SetWindowTitle(window, str);
		renderer.update();
		event_manager.update();
	}

	// Shutdown modules
	renderer.shutdown();
	event_manager.update();

	SDL_Quit();
	return 0;
}
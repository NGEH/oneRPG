
#define SDL_MAIN_HANDLED

#include <cstdio>

#include <SDL.h>
#include "Renderer.h"
#include "EventManager.h"
#include "InputManager.h"

Renderer renderer;
EventManager event_manager;
InputManager input_manager;

void ExitGame(void*) {
	exit(-1);
}

int x = 0;
int y = 0;

void MoveCharacter(void* charinfo) {
	Movement m = *(Movement*)charinfo;
	
	if (m.direction == 0) x--;
}

int main() {

	bool running = true;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("win", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

	// Initialize modules
	renderer.initialise(window);
	event_manager.initialise();
	input_manager.initialise();

	event_manager.register_subscriber("InputExit", ExitGame);
	event_manager.register_subscriber("InputMovement", MoveCharacter);

	// @Temporary: create an event manager to deal with these
	SDL_Event e;

	while (running) {
		
		{
			//Change the window title to have the x and y coordinates
			char str[32];
			sprintf_s(str, "%d, %d", x, y);
			SDL_SetWindowTitle(window, str);
		}


		renderer.update();
		event_manager.update();
		input_manager.update();
	}

	// Shutdown modules
	renderer.shutdown();
	event_manager.update();
	input_manager.shutdown();


	SDL_Quit();
	return 0;
}
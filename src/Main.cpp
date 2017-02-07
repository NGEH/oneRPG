
#define SDL_MAIN_HANDLED

#include <cstdio>

#include <SDL.h>
#include <SDL_ttf.h>

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
	TTF_Init();

	SDL_Window* window = SDL_CreateWindow("win", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

	// Initialize modules
	renderer.initialise(window);
	event_manager.initialise();
	input_manager.initialise();

	event_manager.register_subscriber("InputExit", ExitGame);
	event_manager.register_subscriber("InputMovement", MoveCharacter);

	// @Temporary: create an event manager to deal with these
	SDL_Event e;
	Font f("arial.ttf");

	while (running) {
		
		{
			//Change the window title to have the x and y coordinates
			char str[32];
			sprintf_s(str, "%d, %d", x, y);
			SDL_SetWindowTitle(window, str);
		}
		
		renderer.clear({ 255,0,0 });
		renderer.draw_rectangle(x, y, 50, 50, { 3,240,180 });
		renderer.draw_text(0, 0, "Hello, World!", f);
		renderer.update();
		event_manager.update();
		input_manager.update();
	}

	// Shutdown modules
	renderer.shutdown();
	event_manager.update();
	input_manager.shutdown();

	TTF_Quit();
	SDL_Quit();
	return 0;
}
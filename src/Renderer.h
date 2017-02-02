#pragma once

#include <SDL.h>

const int WIDTH = 800;
const int HEIGHT = 600;

struct Renderer {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;


public:
	void initialise(SDL_Window* window);
	void shutdown();

	void update();

};

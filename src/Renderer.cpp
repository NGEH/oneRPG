#include "Renderer.h"

void Renderer::initialise(SDL_Window* window) {
	this->window = window;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void Renderer::shutdown() {
	if (renderer) SDL_DestroyRenderer(renderer);
	if (window)   SDL_DestroyWindow(window);


}

void Renderer::update() {
	SDL_RenderClear(renderer);


	SDL_RenderPresent(renderer);
}

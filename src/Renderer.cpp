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
	SDL_RenderPresent(renderer);
}

void Renderer::draw_rectangle(int x, int y, int width, int height, Colour colour) {
	SDL_SetRenderDrawColor(renderer, colour.red, colour.green, colour.blue, 255);
	SDL_Rect r = { x, y, width, height };
	SDL_RenderFillRect(renderer, &r);
}

void Renderer::draw_circle(int x, int y, int radius, Colour colour) {
	SDL_SetRenderDrawColor(renderer, colour.red, colour.green, colour.blue, 255);

}

void Renderer::draw_sprite(int x, int y, Sprite spr) {
}

void Renderer::draw_background() {
}

void Renderer::draw_text(int x, int y, const char * string, Font font) {
	SDL_Color color = { font.colour.red , font.colour.green, font.colour.blue };
	
	
	SDL_Surface *text_surface;
	if (!(text_surface = TTF_RenderText_Blended(font.typeface, string, color))) {
		//handle error here, perhaps print TTF_GetError at least
	}
	else {
		SDL_Texture* t = SDL_CreateTextureFromSurface(renderer, text_surface);
		SDL_Rect src = { 0, 0, 200, 12 };
		SDL_Rect dst = { x, y, 200, 12 };
		SDL_RenderCopy(renderer, t, &src, &dst);
		//SDL_BlitSurface(text_surface, NULL, screen, NULL);
		//perhaps we can reuse it, but I assume not for simplicity.
		SDL_FreeSurface(text_surface);
	}
}	

void Renderer::clear(Colour colour) {
	SDL_SetRenderDrawColor(renderer, colour.red, colour.green, colour.blue, 255);
	SDL_RenderClear(renderer);
}

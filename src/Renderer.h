#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

const int WIDTH = 800;
const int HEIGHT = 600;



struct Colour {
	union {
		struct {
			int red;
			int green;
			int blue;
		};

		struct {
			int r, g, b;
		};
	};
};


struct Font {
	Font(const char* name, int size = 12, Colour colour = { 0, 0, 0 }) {
		typeface = TTF_OpenFont("Inconsolata-Regular.ttf", size);
		const char* error = TTF_GetError();
		this->size = size;
		this->colour = colour;
	}

	TTF_Font* typeface; // = "Some game font";
	Colour colour;
	int size;
};

struct Sprite {

};

/*
 *  Renderer::draw_rectangle(x, y, width, height); 
 *  Renderer::draw_circle(x, y, radius);
 *  Renderer::draw_sprite(x, y, sprite);
 *  Renderer::draw_background(???);
 *  Renderer::clear(colour);
 */
struct Renderer {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;


public:
	void initialise(SDL_Window* window);
	void shutdown();

	void update();

	void clear(Colour colour);

	//Primitive functions:
	void draw_rectangle(int x, int y, int width, int height, Colour colour);
	void draw_circle(int x, int y, int radius, Colour colour);
	void draw_sprite(int x, int y, Sprite spr);

	//Middle functions:
	void draw_background();
	void draw_text(int x, int y, const char* string, Font font);
};

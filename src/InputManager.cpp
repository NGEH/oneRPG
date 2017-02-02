#pragma once

#include "InputManager.h"
#include <SDL.h>
#include "EventManager.h"

extern EventManager event_manager;

void InputManager::initialise() {

}

void InputManager::update() {
	SDL_Event e;

	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym == SDLK_ESCAPE) {
				event_manager.push_event("InputExit", nullptr);
			}

			Movement* m = new Movement();
			m->speed = 255;
			
			switch (e.key.keysym.sym) {
			case SDLK_w:
				m->direction = 0;
				event_manager.push_event("InputMovement", (void*)m);
				break;

			case SDLK_a:
				m->direction = 192;
				event_manager.push_event("InputMovement", (void*)m);
				break;

			case SDLK_s:
				m->direction = 128;
				event_manager.push_event("InputMovement", (void*)m);
				break;

			case SDLK_d:
				m->direction = 64;
				event_manager.push_event("InputMovement", (void*)m);
				break;
			}
		}
	}


}

void InputManager::shutdown() {
	
}

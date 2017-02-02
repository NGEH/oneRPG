#include "EventManager.h"

#include "SDL.h"


unsigned int fnv1a(std::string& str) {
	const unsigned int offset_basis = 2166136261;
	const unsigned int fnv_prime = 16777619;

	unsigned int hash = offset_basis;

	for (auto c : str) {
		hash ^= c;
		hash *= fnv_prime;
	}

	return hash;
}

void EventManager::update() {
	
	Event ev;
	while (events.size() > 0) {
		ev = events.front();
		if (subscribers.exists(ev.name)) {
			Subscriber s = subscribers[ev.name];
			printf("Event: %s\n", ev.name.c_str());
			s.proc(ev.arguments);
		}
		events.pop_front();
	}
}

void EventManager::register_subscriber(std::string event_name, EventProc callback) {
	subscribers[event_name] = Subscriber{ event_name, callback };
}

void EventManager::push_event(std::string str, void* arg) {
	events.push_back({ str, arg });
}

#pragma once

#include "HashTable.h"
#include <deque>

#include <string>

typedef void(*EventProc)(void*);

struct Event {
	std::string name;
	void* arguments;
};

struct Subscriber {
	std::string name;
	EventProc proc;
};

struct Movement {
	unsigned char direction;
	unsigned char speed;
};

unsigned int fnv1a(std::string& str);

struct EventManager {
	HashTable<std::string, Subscriber> subscribers = HashTable<std::string, Subscriber>(fnv1a, 32);
	std::deque<Event> events;

	void initialise() {};
	void update();
	void shutdown() {};

	void push_event(std::string str, void* arg);
	void register_subscriber(std::string event_name, EventProc callback);
};

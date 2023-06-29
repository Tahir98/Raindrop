#include "Scene.h"

static uint32_t idCounter = 0;


Engine::Scene::Scene(std::string name, Window& window) : name(name), window(window) {
	id = idCounter++;
}

Engine::Scene::~Scene() {

}

uint32_t Engine::Scene::getID() {
	return id;
}

std::string Engine::Scene::getName()
{
	return name;
}

Engine::Window Engine::Scene::getWindow() {
	return window;
}

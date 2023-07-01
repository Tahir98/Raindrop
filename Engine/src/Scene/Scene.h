#pragma once 
#include <string>
#include "Window/Window.h"

namespace Engine {

	class Scene {
	protected:
		uint32_t id;
		std::string name;
		Window& window;

	public:
		Scene(std::string name, Window& window);
		virtual ~Scene();

		virtual void OnCreate() = 0;
		virtual void OnUpdate(float delta) = 0;
		virtual void OnSuspend() = 0;
		virtual void OnResume() = 0;
		virtual void OnDestroy() = 0;

		uint32_t getID();
		std::string getName();
		Window getWindow();
	};
}
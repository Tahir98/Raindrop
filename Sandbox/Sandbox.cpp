#include <Engine.h>
#include "Scenes/ExampleScene.h"


class SandboxApp : public Engine::Application {
public:
	SandboxApp() : Engine::Application() {

	}

	~SandboxApp() override {

	}

	void run() override {
		Engine::Window window("App",1600,900,false,false, true);

		ExampleScene scene("Example Scene", window);

		Engine::SceneManager::pushScene(&scene);

		while (!window.ShouldClose()) {
			window.Update();

			window.PostEvents();
		}

		Engine::SceneManager::clearAll();
	}
};

Engine::Application* Engine::CreateApplication() {
	return new SandboxApp();
}
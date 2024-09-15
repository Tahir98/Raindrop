#include <Engine.h>
//#include "Scenes/ExampleScene.h"
#include "Scenes/VolumeRendering.h"
#include "Scenes/TextureTest.h"
#include "Scenes/ModelTest.h"
#include "Scenes/ComputeShaderTest.h"

class SandboxApp : public Engine::Application {
public:
	SandboxApp() : Engine::Application() {

	}

	~SandboxApp() override {

	}

	void run() override {
		Engine::Window window("App", 1600, 900, false, false, true);
	
		ComputeShaderTest scene("Compute Shader Test", window);
		
		//ModelTest scene("Volume Rendering", window);

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
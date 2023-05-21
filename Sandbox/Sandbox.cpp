
#include <Engine.h>

class SandboxApp : public Engine::Application {
public:
	SandboxApp() : Engine::Application() {

	}

	~SandboxApp() override {

	}

	void run() override {
		Engine::Window window("App",1600,900,false);

		while (!window.ShouldClose()) {
			window.Update();


			window.PostEvents();
		}
	}
};

Engine::Application* Engine::CreateApplication() {
	return new SandboxApp();
}
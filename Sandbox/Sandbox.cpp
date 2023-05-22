
#include <Engine.h>

class SandboxApp : public Engine::Application {
public:
	SandboxApp() : Engine::Application() {

	}

	~SandboxApp() override {

	}

	void run() override {
		Engine::Window window("App",1600,900,false);

		float tris[9] = {
			-0.5f, -0.5f,
			0.5f, -0.5f,
			0, -0.5f
		};

		Engine::VertexBuffer vb(tris, sizeof(tris), GL_STATIC_DRAW);
		Engine::VertexArray va;

		va.PushElement(&vb, 2, Engine::VertexArray::FLOAT, false);

		Engine::Shader shader("Shaders/Basic.shader");

		while (!window.ShouldClose()) {
			window.Update();

			va.bind();
			shader.bind();

			glDrawArrays(GL_TRIANGLES, 0, 3);

			window.PostEvents();
		}
	}
};

Engine::Application* Engine::CreateApplication() {
	return new SandboxApp();
}
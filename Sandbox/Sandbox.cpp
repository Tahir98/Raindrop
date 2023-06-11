
#include <Engine.h>

class SandboxApp : public Engine::Application {
public:
	SandboxApp() : Engine::Application() {

	}

	~SandboxApp() override {

	}

	void run() override {
		Engine::Window window("App",1600,900,false);

		
		std::vector<glm::vec3> tris;

		tris.push_back(glm::vec3(-0.5f, -0.5f, 0));
		tris.push_back(glm::vec3(1, 0, 0));
		tris.push_back(glm::vec3(0.5f, -0.5f, 0));
		tris.push_back(glm::vec3(0, 1, 0));
		tris.push_back(glm::vec3(0, 0.5f, 0));
		tris.push_back(glm::vec3(0, 0, 1));

		Engine::VertexBuffer vb(tris.data(), sizeof(glm::vec3) * tris.size(), GL_STATIC_DRAW);
		Engine::VertexArray va;

		va.PushElement(&vb, 3, Engine::VertexArray::FLOAT, false);
		va.PushElement(&vb, 3, Engine::VertexArray::FLOAT, false);

		//uint32_t vb_id;
		//glGenBuffers(1, &vb_id);
		//glBindBuffer(GL_ARRAY_BUFFER, vb_id);
		//glBufferData(GL_ARRAY_BUFFER, 6 * 4, tris, GL_STATIC_DRAW);
		//
		Engine::Shader shader("Shaders/Basic.shader");



		while (!window.ShouldClose()) {
			window.Update();

			vb.bind(); 

			va.bind();
			shader.bind();

			shader.SetUniform3f("uColor", 1, 1,1);

			glDrawArrays(GL_TRIANGLES, 0, 3);

			int error;
			while ((error = glGetError()) != GL_NO_ERROR) {
				APP_LOG_ERROR("Opengl Error: {0}", error);
			}


			window.PostEvents();
		}
	}
};

Engine::Application* Engine::CreateApplication() {
	return new SandboxApp();
}
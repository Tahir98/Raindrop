#pragma once

#ifdef GRAPHICS_API_OPENGL
#include <glad/glad.h>
#elif GRAPHICS_API_DIRECTX
//TODO Alperen
#endif 

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>

#ifndef LOG_INPUTS
	//#define LOG_INPUTS
#endif // !LOG_INPUTS


namespace Engine {
	class Window {
	public:
		struct WindowProperties {
			std::string name;
			uint32_t width, height;
			GLFWwindow* nativeWindowPtr = nullptr;
			bool fullscreen;
			bool vsync;
			bool dockspaceEnabled;
		};
	private:
		WindowProperties properties;
		float deltaTime;
		float time_prev = 0, time_now = 0;

		void AddCallbackFunctions();
	public:

		Window(std::string name, uint32_t width, uint32_t height, bool fullscreen, bool vsync = true, bool dockspaceEnabled = true);
		~Window();

		GLFWwindow* GetNativeWindowPtr();

		void Update();
		void PostEvents();
		float GetDeltaTime();
		void Resize(const uint32_t width, const uint32_t height);
		bool ShouldClose();
		WindowProperties getWindowProperties();
	};
}



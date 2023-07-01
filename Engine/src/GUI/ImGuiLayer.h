#pragma once
#include "Window/Window.h"

namespace Engine {
	class ImGuiLayer {
	public:
		static void InitImGui(Window& currentWindow);
		static void StartNewFrame();
		static void RenderNewFrame();
		static void Shutdown();
	};
}

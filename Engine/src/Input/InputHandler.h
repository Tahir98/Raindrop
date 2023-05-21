#pragma once 
#include "InputDefines.h"
#include "Log.h"
#include <utility>
#include <unordered_map>
#include <vector>
#include "Application.h"
#include <glm/glm.hpp>


namespace Engine {

	class InputHandler {
		friend class Application;
		friend class Window;
		
		friend class KeyPressedEvent;
		friend class KeyReleasedEvent;
		friend class KeyRepeatedEvent;

		friend class MouseButtonPressedEvent;
		friend class MouseButtonReleasedEvent;
		friend class MouseMovedEvent;
		friend class MouseScrolledEvent;

	private:
		struct KeyState {
			bool isPressed;
			bool isRepeat;
			bool isReleased;
		};

		struct ButtonState {
			bool isPressed;
			bool isRepeat;
			bool isReleased;
		};

		static std::unordered_map<int, KeyState> keys;
		static std::unordered_map<int, ButtonState> mouseButtons;

		static std::vector<std::pair<int,int>> tempKeyBuffer;
		static std::vector<std::pair<int,int>> tempButtonBuffer;

		static void Init();
		static void UpdateTemporaryBuffers();

		static glm::vec2 mouseScroll;
		static glm::vec2 mousePosition;

		//Window class will assign values throug this methods
		static void SetMouseScrollOffset(glm::vec2 offset);
		static void SetMousePosition(glm::vec2 position);

		static void SetMouseScrollOffset(float xoffset, float yoffset);
		static void SetMousePosition(float xpos, float ypos);

		static void SetKeyState(int keycode, int action);
		static void SetMouseButtonState(int buttoncode, int action);

	public:
		static bool KeyDown(int keycode);
		static bool KeyUp(int keycode);
		static bool Key(int keycode);

		static bool MouseButtonDown(int buttoncode);
		static bool MouseButtonUp(int buttoncode);
		static bool MouseButton(int buttoncode);

		static glm::vec2 MouseScroll();
		static glm::vec2 MousePosition();
	};
}
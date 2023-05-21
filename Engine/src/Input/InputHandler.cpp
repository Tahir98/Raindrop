#include "InputHandler.h"
#include <GLFW/glfw3.h>

namespace Engine {
	std::unordered_map<int, InputHandler::KeyState> InputHandler::keys;
	std::unordered_map<int, InputHandler::ButtonState> InputHandler::mouseButtons;

	std::vector<std::pair<int, int>> InputHandler::tempKeyBuffer;
	std::vector<std::pair<int, int>> InputHandler::tempButtonBuffer;

	glm::vec2 InputHandler::mouseScroll;
	glm::vec2 InputHandler::mousePosition;

	void InputHandler::Init() {
		/* The unknown key */
		keys[KEY_UNKNOWN] = { false, false, false };

		/* Printable keys */
		keys[KEY_SPACE] = { false, false, false };
		keys[KEY_APOSTROPHE] = { false, false, false };
		keys[KEY_COMMA] = { false, false, false };
		keys[KEY_MINUS] = { false, false, false };
		keys[KEY_PERIOD] = { false, false, false };
		keys[KEY_SLASH] = { false, false, false };
		keys[KEY_0] = { false, false, false };
		keys[KEY_1] = { false, false, false };
		keys[KEY_2] = { false, false, false };
		keys[KEY_3] = { false, false, false };
		keys[KEY_4] = { false, false, false };
		keys[KEY_5] = { false, false, false };
		keys[KEY_6] = { false, false, false };
		keys[KEY_7] = { false, false, false };
		keys[KEY_8] = { false, false, false };
		keys[KEY_9] = { false, false, false };
		keys[KEY_SEMICOLON] = { false, false, false };
		keys[KEY_EQUAL] = { false, false, false };
		keys[KEY_A] = { false, false, false };
		keys[KEY_B] = { false, false, false };
		keys[KEY_C] = { false, false, false };
		keys[KEY_D] = { false, false, false };
		keys[KEY_E] = { false, false, false };
		keys[KEY_F] = { false, false, false };
		keys[KEY_G] = { false, false, false };
		keys[KEY_H] = { false, false, false };
		keys[KEY_I] = { false, false, false };
		keys[KEY_J] = { false, false, false };
		keys[KEY_K] = { false, false, false };
		keys[KEY_L] = { false, false, false };
		keys[KEY_M] = { false, false, false };
		keys[KEY_N] = { false, false, false };
		keys[KEY_O] = { false, false, false };
		keys[KEY_P] = { false, false, false };
		keys[KEY_Q] = { false, false, false };
		keys[KEY_R] = { false, false, false };
		keys[KEY_S] = { false, false, false };
		keys[KEY_T] = { false, false, false };
		keys[KEY_U] = { false, false, false };
		keys[KEY_V] = { false, false, false };
		keys[KEY_W] = { false, false, false };
		keys[KEY_X] = { false, false, false };
		keys[KEY_Y] = { false, false, false };
		keys[KEY_Z] = { false, false, false };
		keys[KEY_LEFT_BRACKET] = { false, false, false };
		keys[KEY_BACKSLASH] = { false, false, false };
		keys[KEY_RIGHT_BRACKET] = { false, false, false };
		keys[KEY_GRAVE_ACCENT] = { false, false, false };
		keys[KEY_WORLD_1] = { false, false, false };
		keys[KEY_WORLD_2] = { false, false, false };

		/* Function keys */
		keys[KEY_ESCAPE] = { false, false, false };
		keys[KEY_ENTER] = { false, false, false };
		keys[KEY_TAB] = { false, false, false };
		keys[KEY_BACKSPACE] = { false, false, false };
		keys[KEY_INSERT] = { false, false, false };
		keys[KEY_DELETE] = { false, false, false };
		keys[KEY_RIGHT] = { false, false, false };
		keys[KEY_LEFT] = { false, false, false };
		keys[KEY_DOWN] = { false, false, false };
		keys[KEY_UP] = { false, false, false };
		keys[KEY_PAGE_UP] = { false, false, false };
		keys[KEY_PAGE_DOWN] = { false, false, false };
		keys[KEY_HOME] = { false, false, false };
		keys[KEY_END] = { false, false, false };
		keys[KEY_CAPS_LOCK] = { false, false, false };
		keys[KEY_SCROLL_LOCK] = { false, false, false };
		keys[KEY_NUM_LOCK] = { false, false, false };
		keys[KEY_PRINT_SCREEN] = { false, false, false };
		keys[KEY_PAUSE] = { false, false, false };
		keys[KEY_F1] = { false, false, false };
		keys[KEY_F2] = { false, false, false };
		keys[KEY_F3] = { false, false, false };
		keys[KEY_F4] = { false, false, false };
		keys[KEY_F5] = { false, false, false };
		keys[KEY_F6] = { false, false, false };
		keys[KEY_F7] = { false, false, false };
		keys[KEY_F8] = { false, false, false };
		keys[KEY_F9] = { false, false, false };
		keys[KEY_F10] = { false, false, false };
		keys[KEY_F11] = { false, false, false };
		keys[KEY_F12] = { false, false, false };
		keys[KEY_F13] = { false, false, false };
		keys[KEY_F14] = { false, false, false };
		keys[KEY_F15] = { false, false, false };
		keys[KEY_F16] = { false, false, false };
		keys[KEY_F17] = { false, false, false };
		keys[KEY_F18] = { false, false, false };
		keys[KEY_F19] = { false, false, false };
		keys[KEY_F20] = { false, false, false };
		keys[KEY_F21] = { false, false, false };
		keys[KEY_F22] = { false, false, false };
		keys[KEY_F23] = { false, false, false };
		keys[KEY_F24] = { false, false, false };
		keys[KEY_F25] = { false, false, false };
		keys[KEY_KP_0] = { false, false, false };
		keys[KEY_KP_1] = { false, false, false };
		keys[KEY_KP_2] = { false, false, false };
		keys[KEY_KP_3] = { false, false, false };
		keys[KEY_KP_4] = { false, false, false };
		keys[KEY_KP_5] = { false, false, false };
		keys[KEY_KP_6] = { false, false, false };
		keys[KEY_KP_7] = { false, false, false };
		keys[KEY_KP_8] = { false, false, false };
		keys[KEY_KP_9] = { false, false, false };
		keys[KEY_KP_DECIMAL] = { false, false, false };
		keys[KEY_KP_DIVIDE] = { false, false, false };
		keys[KEY_KP_MULTIPLY] = { false, false, false };
		keys[KEY_KP_SUBTRACT] = { false, false, false };
		keys[KEY_KP_ADD] = { false, false, false };
		keys[KEY_KP_ENTER] = { false, false, false };
		keys[KEY_KP_EQUAL] = { false, false, false };
		keys[KEY_LEFT_SHIFT] = { false, false, false };
		keys[KEY_LEFT_CONTROL] = { false, false, false };
		keys[KEY_LEFT_ALT] = { false, false, false };
		keys[KEY_LEFT_SUPER] = { false, false, false };
		keys[KEY_RIGHT_SHIFT] = { false, false, false };
		keys[KEY_RIGHT_CONTROL] = { false, false, false };
		keys[KEY_RIGHT_ALT] = { false, false, false };
		keys[KEY_RIGHT_SUPER] = { false, false, false };
		keys[KEY_MENU] = { false, false, false };

		/*Mouse Buttons*/
		mouseButtons[MOUSE_BUTTON_1] = { false, false, false };
		mouseButtons[MOUSE_BUTTON_2] = { false, false, false };
		mouseButtons[MOUSE_BUTTON_3] = { false, false, false };
		mouseButtons[MOUSE_BUTTON_4] = { false, false, false };
		mouseButtons[MOUSE_BUTTON_5] = { false, false, false };
		mouseButtons[MOUSE_BUTTON_6] = { false, false, false };
		mouseButtons[MOUSE_BUTTON_7] = { false, false, false };
		mouseButtons[MOUSE_BUTTON_8] = { false, false, false };
		mouseButtons[MOUSE_BUTTON_LAST] = { false, false, false };
		mouseButtons[MOUSE_BUTTON_LEFT] = { false, false, false };
		mouseButtons[MOUSE_BUTTON_RIGHT] = { false, false, false };
		mouseButtons[MOUSE_BUTTON_MIDDLE] = { false, false, false };

		mouseScroll.x = 0;
		mouseScroll.y = 0;
	}

	void InputHandler::UpdateTemporaryBuffers() {
		for (int i = 0; i < tempKeyBuffer.size();i++) {
			int key = tempKeyBuffer[i].first;
			int action = tempKeyBuffer[i].second;

			if (action == GLFW_PRESS) {
				keys[key].isPressed = false;
				keys[key].isRepeat = true;
			}
			else if (action == GLFW_RELEASE) {
				keys[key].isPressed = false;
				keys[key].isRepeat = false;
				keys[key].isReleased = false;
			}
		}

		tempKeyBuffer.clear();

		for (int i = 0; i < tempButtonBuffer.size(); i++) {
			int button = tempButtonBuffer[i].first;
			int action = tempButtonBuffer[i].second;

			if (action == GLFW_PRESS) {
				mouseButtons[button].isPressed = false;
				mouseButtons[button].isRepeat = true;
			}
			else if (action == GLFW_RELEASE) {
				mouseButtons[button].isPressed = false;
				mouseButtons[button].isRepeat = false;
				mouseButtons[button].isReleased = false;
			}
		}

		tempButtonBuffer.clear();
	}

	void InputHandler::SetMouseScrollOffset(glm::vec2 offset){
		mouseScroll =  offset;
	}

	void InputHandler::SetMousePosition(glm::vec2 position) {
		mousePosition = position;
	}

	void InputHandler::SetMouseScrollOffset(float xoffset, float yoffset) {
		mouseScroll = glm::vec2(xoffset, yoffset);
	}

	void InputHandler::SetMousePosition(float xpos, float ypos) {
		mousePosition = glm::vec2(xpos, ypos);
	}

	void InputHandler::SetKeyState(int keycode, int action) {
		if (action == GLFW_PRESS) {
			InputHandler::keys[keycode].isPressed = true;
		}
		else if (action == GLFW_REPEAT) {
			InputHandler::keys[keycode].isRepeat = true;
		}
		else if (action == GLFW_RELEASE) {
			InputHandler::keys[keycode].isPressed = false;
			InputHandler::keys[keycode].isRepeat = false;
			InputHandler::keys[keycode].isReleased = true;
		}

		InputHandler::tempKeyBuffer.push_back({ keycode, action });
	}

	void InputHandler::SetMouseButtonState(int buttoncode, int action) {
		if (action == GLFW_PRESS) {
			InputHandler::mouseButtons[buttoncode].isPressed = true;
			InputHandler::mouseButtons[buttoncode].isRepeat = true;
		}
		else if (action == GLFW_RELEASE) {
			InputHandler::mouseButtons[buttoncode].isPressed = false;
			InputHandler::mouseButtons[buttoncode].isRepeat = false;
			InputHandler::mouseButtons[buttoncode].isReleased = true;
		}
		
		InputHandler::tempButtonBuffer.push_back({ buttoncode, action });
	}

	bool InputHandler::KeyDown(int keycode) {
		return keys[keycode].isPressed;
	}

	bool InputHandler::KeyUp(int keycode){
		return keys[keycode].isReleased;
	}

	bool InputHandler::Key(int keycode) {
		return keys[keycode].isRepeat || keys[keycode].isPressed;
	}

	bool InputHandler::MouseButtonDown(int buttoncode) {
		return mouseButtons[buttoncode].isPressed;
	}

	bool InputHandler::MouseButtonUp(int buttoncode) {
		return mouseButtons[buttoncode].isReleased;
	}

	bool InputHandler::MouseButton(int buttoncode) {
		return mouseButtons[buttoncode].isPressed || mouseButtons[buttoncode].isRepeat;
	}

	glm::vec2 InputHandler::MouseScroll() {
		return mouseScroll;
	}

	glm::vec2 InputHandler::MousePosition() {
		return mousePosition;
	}
}
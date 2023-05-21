#pragma once
#include "Event.h"
#include "Input/InputHandler.h"


namespace Engine {
	class MouseButtonPressedEvent : public Event {
	private:
		int button;
	public:
		MouseButtonPressedEvent(int button) : button(button) {
			category = EventCategory::MouseEvent;
			type = EventType::MouseButtonPressed;

			InputHandler::SetMouseButtonState(button, GLFW_PRESS);
		}

		std::string getMessage() {
			return ("Mouse Button Pressed Event, button: " + std::to_string(button));
		}

		int getButton() {
			return button;
		}
	};

	class MouseButtonReleasedEvent : public Event {
	private:
		int button;
	public:
		MouseButtonReleasedEvent(int button) : button(button) {
			category = EventCategory::MouseEvent;
			type = EventType::MouseButtonReleased;

			InputHandler::SetMouseButtonState(button, GLFW_RELEASE);
		}

		std::string getMessage() {
			return ("Mouse Button Released Event, button: " + std::to_string(button));
		}

		int getButton() {
			return button;
		}
	};

	class MouseMovedEvent : public Event {
	private:
		float x, y;
	public:
		MouseMovedEvent(float x, float y) : x(x), y(y) {
			category = EventCategory::MouseEvent;
			type = EventType::MouseMoved;

			InputHandler::SetMousePosition(x, y);
		}

		std::string getMessage() {
			return ("Mouse Moved Event, x: " + std::to_string(x) + " y: " + std::to_string(y));
		}

		float getX() {
			return x;
		}

		float getY() {
			return y;
		}
	};

	class MouseScrolledEvent : public Event {
	private:
		float xoffset, yoffset;
	public:
		MouseScrolledEvent(float xoffset, float yoffset) : xoffset(xoffset), yoffset(yoffset) {
			category = EventCategory::MouseEvent;
			type = EventType::MouseScrolled;

			InputHandler::SetMouseScrollOffset(xoffset, yoffset);
		}

		std::string getMessage() {
			return ("Mouse Scrolled Event, xoffset: " + std::to_string(xoffset) + " yoffset: " + std::to_string(yoffset));
		}

		float getXoffset() {
			return xoffset;
		}

		float getYoffset() {
			return yoffset;
		}
	};
}
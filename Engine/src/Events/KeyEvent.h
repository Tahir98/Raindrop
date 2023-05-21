#pragma once

#include "Event.h"
#include "Input/InputHandler.h"
/*
enum class EventType {
		WindowMoved, WindowResized, WindowClosed,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
		KeyPressed, KeyReleased, KeyRepeated
	};
*/

namespace Engine {
	class KeyPressedEvent : public Event {
	private:
		int key;
	public:
		KeyPressedEvent(int key) : key(key){
			category = EventCategory::KeyEvent;
			type = EventType::KeyPressed;

			InputHandler::SetKeyState(key, GLFW_PRESS);
		}

		std::string getMessage() {
			return ("Key Pressed Event, keycode:" + std::to_string(key));
		}

		int getKey() {
			return key;
		}
	};

	class KeyReleasedEvent : public Event {
	private:
		int key;
	public:
		KeyReleasedEvent(int key) : key(key) {
			category = EventCategory::KeyEvent;
			type = EventType::KeyReleased;

			InputHandler::SetKeyState(key, GLFW_RELEASE);
		}

		std::string getMessage() {
			return ("Key Released Event, keycode:" + std::to_string(key));
		}

		int getKey() {
			return key;
		}
	};

	class KeyRepeatedEvent : public Event {
	private:
		int key;
	public:
		KeyRepeatedEvent(int key) : key(key) {
			category = EventCategory::KeyEvent;
			type = EventType::KeyRepeated;

			InputHandler::SetKeyState(key, GLFW_REPEAT);
		}

		std::string getMessage() {
			return ("Key Repeated Event, keycode:" + std::to_string(key));
		}

		int getKey() {
			return key;
		}
	};
}

#pragma once

#include <string>

namespace Engine {
	enum class EventCategory {
		WindowEvent = 0,
		MouseEvent = 1,
		KeyEvent = 2
	};

	enum class EventType {
		WindowMoved, WindowResized, WindowClosed,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
		KeyPressed, KeyReleased, KeyRepeated
	};

	class Event {
	public:
		EventCategory category;
		EventType type;

		virtual std::string getMessage() = 0;
	};
}




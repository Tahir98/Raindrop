#pragma once

#include "Event.h"

namespace Engine {
	class WindowMovedEvent : public Event {
	private:
		int x, y;
	public:
		WindowMovedEvent(int x, int y) : x(x), y(y) {
			category = EventCategory::WindowEvent;
			type = EventType::WindowMoved;
		}

		std::string getMessage() {
			return ("Window Moved Event, x:" + std::to_string(x) + " y: " + std::to_string(y));
		}

		int getX() {
			return x;
		}

		int getY() {
			return y;
		}
	};

	class WindowResizedEvent : public Event {
	private:
		int width, height;
	public:
		WindowResizedEvent(int width, int height) : width(width), height(height) {
			category = EventCategory::WindowEvent;
			type = EventType::WindowResized;
		}

		std::string getMessage() {
			return ("Window Resized Event, width: " + std::to_string(width) + " height: " + std::to_string(height));
		}

		int getWidth() {
			return width;
		}

		int getHeight() {
			return height;
		}
	};

	class WindowClosedEvent : public Event {
	public:
		WindowClosedEvent() {
			category = EventCategory::WindowEvent;
			type = EventType::WindowClosed;
		}

		std::string getMessage() {
			return ("Window Closed Event");
		}
	};
}
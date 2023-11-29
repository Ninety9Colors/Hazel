#pragma once

#include "Event.h"

namespace Hazel {

	class HAZEL_API KeyEvent : public Event
	{
	public:
		inline int get_keycode() const { return keycode_; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keycode)
			: keycode_(keycode) {}

		int keycode_;
	};

	class HAZEL_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), repeat_count_(repeatCount) {}

		inline int getRepeatCount() const { return repeat_count_; }

		std::string to_string() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << keycode_ << " (" << repeat_count_ << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int repeat_count_;
	};

	class HAZEL_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string to_string() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << keycode_;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}
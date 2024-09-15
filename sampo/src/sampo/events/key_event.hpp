#pragma once
#include "event.hpp"

#include <sstream>

namespace Sampo
{
	class KeyEvent : public Event
	{
	public:
		int GetKeyCode() const { return m_KeyCode; }
		
		EVENT_CLASS_CATEGORY(Keyboard | Input)
	protected:
		KeyEvent(int aKeyCode) : m_KeyCode(aKeyCode) { }

		int m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int aKeyCode, int aRepeatCount) : KeyEvent(aKeyCode), m_RepeatCount(aRepeatCount) {}

		int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressed Event: " << m_KeyCode << "(" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	protected:
		int m_RepeatCount;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int aKeyCode) : KeyEvent(aKeyCode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleased Event: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}
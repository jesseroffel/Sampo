#pragma once
#include "event.hpp"

#include <sstream>
namespace Sampo
{
	class GamepadConnectionEvent : public Event
	{
	public:
		int GetJoystickID() const { return m_JoystickId; }

		EVENT_CLASS_CATEGORY(EventGamepad | EventInput)
	protected:
		GamepadConnectionEvent(int aJoystickId) : m_JoystickId(aJoystickId) {}

		int m_JoystickId{ -1 };
	};

	class GamepadConnectedEvent : public GamepadConnectionEvent
	{
	public:
		GamepadConnectedEvent(int aJoystickId) : GamepadConnectionEvent(aJoystickId) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Gamepad Connected ID: " << m_JoystickId;
			return ss.str();
		}

		EVENT_CLASS_TYPE(JoystickConnected)
	};

	class GamepadDisconnectedEvent : public GamepadConnectionEvent
	{
	public:
		GamepadDisconnectedEvent(int aJoystickId) : GamepadConnectionEvent(aJoystickId) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Gamepad Disconnected, ID: " << m_JoystickId;
			return ss.str();
		}

		EVENT_CLASS_TYPE(JoystickDisconnected)
	};
}
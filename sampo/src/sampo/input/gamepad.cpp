#include "sampo_pch.hpp"
#include "gamepad.hpp"

#include "sampo/events/gamepad_event.hpp"

#include "input_mapping.hpp"

namespace Sampo
{
	Gamepad::Gamepad(int aPlatformId)
		: InputDevice(InputType::kGamepad)
		, m_PlatformId(aPlatformId)
	{
	}

	bool Gamepad::IsValidButton(GamepadButton aGamepadButton) const
	{
		const uint32 index = static_cast<uint32>(aGamepadButton);
		return index >= static_cast<uint32>(GamepadButton::kActionDown) && index <= static_cast<uint32>(GamepadButton::kDpadRight);
	}

	bool Gamepad::IsValidAxis(GamepadAxis aGamepadAxis) const
	{
		const uint32 index = static_cast<uint32>(aGamepadAxis);
		return index >= static_cast<uint32>(GamepadAxis::kLeftX) && index <= static_cast<uint32>(GamepadAxis::kRightTrigger);
	}

	void Gamepad::SetButtonState(GamepadButton aGamepadButton, bool aIsDown)
	{
		if (!IsValidButton(aGamepadButton))
			return;

		const uint32 index = static_cast<uint32>(aGamepadButton);
		m_Buttons[index] = aIsDown;
	}

	bool Gamepad::GetIsButtonPressed(GamepadButton aGamepadButton) const
	{
		if (!IsValidButton(aGamepadButton))
			return false;

		const uint32 index = static_cast<uint32>(aGamepadButton);
		return m_Buttons[index];
	}

	void Gamepad::SetAxisState(GamepadAxis aGamepadAxis, float aValue)
	{
		if (!IsValidAxis(aGamepadAxis))
			return;

		float clampedValue = std::clamp(aValue, -1.0f, 1.0f);

		const uint32 index = static_cast<uint32>(aGamepadAxis);
		m_Axes[index] = clampedValue;
	}

	float Gamepad::GetGamepadAxis(GamepadAxis aGamepadAxis) const
	{
		if (!IsValidAxis(aGamepadAxis))
			return 0.0f;

		const uint32 index = static_cast<uint32>(aGamepadAxis);
		return m_Axes[index];
	}

	int Gamepad::GetPlatformIdFromEvent(Event& aGamepadEvent)
	{
		const EventType eventType = aGamepadEvent.GetEventType();

		if (eventType == EventType::JoystickConnected)
		{
			GamepadConnectedEvent& connectedEvent = static_cast<GamepadConnectedEvent&>(aGamepadEvent);
			return connectedEvent.GetJoystickID();
		}
		else if (eventType == EventType::JoystickDisconnected)
		{
			GamepadDisconnectedEvent& disconnectedEvent = static_cast<GamepadDisconnectedEvent&>(aGamepadEvent);
			return disconnectedEvent.GetJoystickID();
		}

		return -1;
	}
}
#pragma once
#include "input_device.hpp"
#include "input_mapping.hpp"

namespace Sampo
{
	class Event;

	class Keyboard : public InputDevice
	{
	public:
		Keyboard();

		bool InitDevice() override { return true; }

		bool IsValidButton(KeyboardButton aKeyboardButton) const;

		void SetButtonState(KeyboardButton aKeyboardButton, bool aIsDown);
		bool GetIsButtonPressed(KeyboardButton aKeyboardButton) const;

		KeyboardButton GetKeyboardButtonFromPlatform(int aKeyboardCode) const;
		void OnKeyboardEvent(Event& aKeyboardEvent);
	private:
		ButtonKeyState m_Keys[104]{ ButtonKeyState::kUp };
	};
}

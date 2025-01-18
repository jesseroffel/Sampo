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


		void SetButtonState(KeyboardButton aKeyboardButton, bool aIsDown);
		bool GetIsButtonPressed(KeyboardButton aKeyboardButton) const;

		static bool IsValidButton(KeyboardButton aKeyboardButton);
		static KeyboardButton GetKeyboardButtonFromPlatform(int aKeyboardCode);

		void OnKeyboardEvent(Event& aKeyboardEvent);

		void ImGuiDebug() override;
	private:
		ButtonKeyState m_Keys[104]{ ButtonKeyState::kUp };
	};
}

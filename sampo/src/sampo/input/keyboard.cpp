#include "sampo_pch.hpp"
#include "keyboard.hpp"

namespace Sampo
{
	Keyboard::Keyboard()
		: InputDevice(InputType::kKeyboard)
	{
	}

	bool Keyboard::IsValidButton(KeyboardButton aKeyboardCode)
	{
		const uint32 index = static_cast<uint32>(aKeyboardCode);
		return index >= static_cast<uint32>(KeyboardButton::kSPACE) && index <= static_cast<uint32>(KeyboardButton::kMENU);
	}

	void Keyboard::SetButtonState(KeyboardButton aKeyboardButton, bool aIsDown)
	{
		if (!IsValidButton(aKeyboardButton))
			return;

		const uint32 index = static_cast<uint32>(aKeyboardButton) - 1;

		const bool repeating = aIsDown && m_Keys[index] == ButtonKeyState::kFalling || m_Keys[index] == ButtonKeyState::kDown;
		const ButtonKeyState keyState = !aIsDown ? ButtonKeyState::kUp : repeating ? ButtonKeyState::kDown : ButtonKeyState::kFalling;
		m_Keys[index] = keyState;
	}

	bool Keyboard::GetIsButtonPressed(KeyboardButton aKeyboardButton) const
	{
		if (!IsValidButton(aKeyboardButton))
			return false;

		const uint32 index = static_cast<uint32>(aKeyboardButton) - 1;
		return m_Keys[index] != ButtonKeyState::kUp;
	}

}
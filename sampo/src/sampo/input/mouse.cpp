#include "sampo_pch.hpp"
#include "mouse.hpp"

namespace Sampo
{
	Mouse::Mouse()
		: InputDevice(InputType::kMouse)
	{
	}

	bool Mouse::InitDevice()
	{
		m_MouseState.m_Enabled = true;
		return true;
	}

	bool Mouse::IsValidButton(MouseButton aMouseButton) const
	{
		const uint32 index = static_cast<uint32>(aMouseButton);
		return index >= static_cast<uint32>(MouseButton::kLeft) && index <= static_cast<uint32>(MouseButton::kButton8);
	}

	void Mouse::SetButtonState(MouseButton aMouseButton, bool aIsDown)
	{
		if (!IsValidButton(aMouseButton))
			return;

		const uint32 index = static_cast<uint32>(aMouseButton) - 1;
		m_MouseState.m_Keys[index] = !aIsDown ? ButtonKeyState::kUp : ButtonKeyState::kDown;
	}

	bool Mouse::GetIsButtonPressed(MouseButton aMouseButton) const
	{
		if (!IsValidButton(aMouseButton))
			return false;

		const uint32 index = static_cast<uint32>(aMouseButton) - 1;
		return m_MouseState.m_Keys[index] != ButtonKeyState::kUp;
	}
}
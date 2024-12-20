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

	bool Mouse::IsValidButton(MouseButton aMouseButton)
	{
		const uint32 index = static_cast<uint32>(aMouseButton);
		if (index >= static_cast<uint32>(MouseButton::kLeftMouse) && index <= static_cast<uint32>(MouseButton::kMouseButton5))
			return true;
		return false;
	}

	void Mouse::SetButtonState(MouseButton aMouseButton, bool aIsDown)
	{
		if (!IsValidButton(aMouseButton))
			return;

		const uint32 index = static_cast<uint32>(aMouseButton);
		m_MouseState.m_Pressed[index] = aIsDown;
	}

	bool Mouse::GetIsButtonPressed(MouseButton aMouseButton) const
	{
		if (!IsValidButton(aMouseButton))
			return false;

		const uint32 index = static_cast<uint32>(aMouseButton);
		return m_MouseState.m_Pressed[index];
	}
}
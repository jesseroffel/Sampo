#include "sampo_pch.hpp"
#include "mouse.hpp"

namespace Sampo
{
	bool Mouse::IsValidButton(MouseButton aMouseButton)
	{
		const uint32 index = static_cast<uint32>(aMouseButton);
		if (index >= static_cast<uint32>(MouseButton::kLeftMouse) && index <= static_cast<uint32>(MouseButton::kRightMouse))
			return true;
		return false;
	}

	void Mouse::SetButtonState(MouseButton aMouseButton, bool aIsDown)
	{
		if (!IsValidButton(aMouseButton))
			return;

		const uint32 index = static_cast<uint32>(aMouseButton);
		m_Pressed[index] = aIsDown;
	}

	bool Mouse::GetIsButtonPressed(MouseButton aMouseButton) const
	{
		if (!IsValidButton(aMouseButton))
			return false;

		const uint32 index = static_cast<uint32>(aMouseButton);
		return m_Pressed[index];
	}
}
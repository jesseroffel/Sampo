#pragma once
#include "mouse.hpp"

namespace Sampo
{
	// Input container class to retrieve input data from
	class Input
	{
	public:
		Input() = default;
		~Input() = default;

		// Buttons
		// Gamepad
		bool IsMousePresent() const;
		glm::vec2 GetMousePosition() const;
		float GetMouseScrollOffset() const;

		void OnMouseEvent(Event& aMouseEvent);

	protected:
		Mouse m_Mouse;
	};
}
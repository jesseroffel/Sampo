#pragma once
#include "input_mapping.hpp"

#include <glm/glm.hpp>

namespace Sampo
{
	class Event;

	class Mouse
	{
	public:
		void SetIsMousePresent(bool aState) { m_Enabled = aState; }
		bool IsPresent() const { return m_Enabled; }

		static bool IsValidButton(MouseButton aMouseButton);

		void SetPosition(const glm::vec2& aPosition) { m_Position = aPosition; }
		void SetScrollOffset(float anOffset) { m_ScrollOffset = anOffset; }
		void SetButtonState(MouseButton aMouseButton, bool aIsDown);

		const glm::vec2& GetPosition() const { return m_Position; }
		float GetScrollOffset() const { return m_ScrollOffset; }
		bool GetIsButtonPressed(MouseButton aMouseButton) const;

		MouseButton GetMouseButtonFromPlatform(int aMouseCode) const;

		void OnMouseEvent(Event& aMouseEvent);

	private:
		glm::vec2 m_Position{ -1, -1 };
		float m_ScrollOffset{ 0.f };
		bool m_Pressed[5]{ false };
		bool m_Enabled{ false };
	};
}
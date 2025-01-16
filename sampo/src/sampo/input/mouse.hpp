#pragma once
#include "input_device.hpp"
#include "input_mapping.hpp"

#include <glm/glm.hpp>

namespace Sampo
{
	class Event;

	struct MouseState
	{
		glm::vec2 m_Position{ -1, -1 };
		glm::vec2 m_ScrollOffset{ 0.f, 0.f };
		ButtonKeyState m_Keys[8]{ ButtonKeyState::kUp };
	};

	class Mouse : public InputDevice
	{
	public:
		Mouse();

		bool IsValidButton(MouseButton aMouseButton) const;

		void SetPosition(const glm::vec2& aPosition) { m_MouseState.m_Position = aPosition; }
		void SetScrollOffset(const glm::vec2& anOffset) { m_MouseState.m_ScrollOffset = anOffset; }
		void SetButtonState(MouseButton aMouseButton, bool aIsDown);

		const glm::vec2& GetPosition() const { return m_MouseState.m_Position; }
		const glm::vec2& GetScrollOffset() const { return m_MouseState.m_ScrollOffset; }
		bool GetIsButtonPressed(MouseButton aMouseButton) const;

		MouseButton GetMouseButtonFromPlatform(int aMouseCode) const;
		const MouseState& GetMouseState() const { return m_MouseState; }

		void OnMouseEvent(Event& aMouseEvent);

		void ImGuiDebug() override;

	private:
		MouseState m_MouseState;
	};
}
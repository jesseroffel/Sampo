#include "sampo_pch.hpp"
#include "input.hpp"

#include "sampo/events/event.hpp"

namespace Sampo
{
	bool Input::IsMousePresent() const
	{
		return m_Mouse.IsPresent();
	}
	glm::vec2 Input::GetMousePosition() const
	{
		return m_Mouse.GetPosition();
	}

	float Input::GetMouseScrollOffset() const
	{
		return m_Mouse.GetScrollOffset();
	}

	void Input::OnMouseEvent(Event& aMouseEvent)
	{
		if (!aMouseEvent.IsInCategory(EventCategory::EventInput))
			return;

		m_Mouse.OnMouseEvent(aMouseEvent);
	}
}
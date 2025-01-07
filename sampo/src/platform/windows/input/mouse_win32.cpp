#include "sampo_pch.hpp"
#include "sampo/input/mouse.hpp"

#include "sampo/events/mouse_event.hpp"

#include <GLFW/glfw3.h>

namespace Sampo
{
	MouseButton Mouse::GetMouseButtonFromPlatform(int aMouseCode) const
	{
		MouseButton button = MouseButton::kUnknownButton;
		switch (aMouseCode)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
		{
			button = MouseButton::kLeft;
			break;
		}
		case GLFW_MOUSE_BUTTON_RIGHT:
		{
			button = MouseButton::kRight;
			break;
		}
		case GLFW_MOUSE_BUTTON_MIDDLE:
		{
			button = MouseButton::kMiddle;
			break;
		}
		case GLFW_MOUSE_BUTTON_4:
		{
			button = MouseButton::kButton4;
			break;
		}
		case GLFW_MOUSE_BUTTON_5:
		{
			button = MouseButton::kButton5;
			break;
		}
		}
		return button;
	}

	void Mouse::OnMouseEvent(Event& aMouseEvent)
	{
		switch (aMouseEvent.GetEventType())
		{
			case EventType::MouseButtonPressed:
			{
				MouseButtonPressedEvent& pressedEvent = static_cast<MouseButtonPressedEvent&>(aMouseEvent);
				SetButtonState(GetMouseButtonFromPlatform(pressedEvent.GetMouseButton()), true);
				break;
			}
			case EventType::MouseButtonReleased:
			{
				MouseButtonReleasedEvent& releasedEvent = static_cast<MouseButtonReleasedEvent&>(aMouseEvent);
				SetButtonState(GetMouseButtonFromPlatform(releasedEvent.GetMouseButton()), false);
				break;
			}
			case EventType::MouseMoved:
			{
				MouseMovedEvent& mouseMoved = static_cast<MouseMovedEvent&>(aMouseEvent);
				SetPosition(mouseMoved.GetMousePosition());
				break;
			}
			case EventType::MouseScrolled:
			{
				MouseScrolledEvent& scrolledEvent = static_cast<MouseScrolledEvent&>(aMouseEvent);
				scrolledEvent.ToString();
				SetScrollOffset(scrolledEvent.GetOffset());
				break;
			}
			default:
			{
				SAMPO_ASSERT_MSG(false, "Non mouse event passed through mouse event handler!");
				break;
			}
		}
	}
}

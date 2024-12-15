#include "sampo_pch.hpp"
#include "sampo/input/mouse.hpp"

#include <GLFW/glfw3.h>
#include "sampo/events/mouse_event.hpp"

namespace Sampo
{
	MouseButton Mouse::GetMouseButtonFromPlatform(int aMouseCode) const
	{
		MouseButton button = MouseButton::kUnknownMouseButton;
		switch (aMouseCode)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
		{
			button = MouseButton::kLeftMouse;
			break;
		}
		case GLFW_MOUSE_BUTTON_RIGHT:
		{
			button = MouseButton::kRightMouse;
			break;
		}
		case GLFW_MOUSE_BUTTON_MIDDLE:
		{
			button = MouseButton::kMiddleMouse;
			break;
		}
		case GLFW_MOUSE_BUTTON_4:
		{
			button = MouseButton::kMouseButton4;
			break;
		}
		case GLFW_MOUSE_BUTTON_5:
		{
			button = MouseButton::kMouseButton5;
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
				SetScrollOffset(scrolledEvent.GetXOffset());
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

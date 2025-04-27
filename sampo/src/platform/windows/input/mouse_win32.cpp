#include "sampo_pch.hpp"
#include "sampo/input/mouse.hpp"

#include "sampo/events/mouse_event.hpp"

#include <GLFW/glfw3.h>
#include <imgui.h>

namespace Sampo
{
	MouseButton Mouse::GetMouseButtonFromPlatform(int aMouseCode) const
	{
		MouseButton button = MouseButton::kUnknownButton;
		switch (aMouseCode)
		{
		case GLFW_MOUSE_BUTTON_LEFT: { button = MouseButton::kLeft; break; }
		case GLFW_MOUSE_BUTTON_RIGHT: { button = MouseButton::kRight; break; }
		case GLFW_MOUSE_BUTTON_MIDDLE: { button = MouseButton::kMiddle;break; }
		case GLFW_MOUSE_BUTTON_4: { button = MouseButton::kButton4; break; }
		case GLFW_MOUSE_BUTTON_5: { button = MouseButton::kButton5; break; }
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

	void Mouse::ImGuiDebug()
	{
		ImGui::Text("Position: %0.f, %0.f", m_MouseState.m_Position.x, m_MouseState.m_Position.y);
		ImGui::Text("Scroll: %0.f, %0.f", m_MouseState.m_ScrollOffset.x, m_MouseState.m_ScrollOffset.y);

		static constexpr ImGuiTableFlags flags = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_Hideable;

		if (ImGui::BeginTable("mousePressed", 5, flags))
		{
			ImGui::TableSetupColumn("Left", ImGuiTableColumnFlags_WidthFixed);
			ImGui::TableSetupColumn("Middle", ImGuiTableColumnFlags_WidthFixed);
			ImGui::TableSetupColumn("Right", ImGuiTableColumnFlags_WidthFixed);
			ImGui::TableSetupColumn("Mouse4", ImGuiTableColumnFlags_WidthFixed);
			ImGui::TableSetupColumn("Mouse5", ImGuiTableColumnFlags_WidthFixed);
			ImGui::TableHeadersRow();

			ImGui::TableNextRow();
			for (int i = 0; i < 5; i++)
			{
				ImGui::TableSetColumnIndex(i);
				ImGui::Text("%d", m_MouseState.m_Keys[i]);
			}

			ImGui::EndTable();
		}
	}
}

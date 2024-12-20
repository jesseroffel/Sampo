#include "sampo_pch.hpp"
#include "input.hpp"

#include "mouse.hpp"
#include "sampo/events/event.hpp"

#include <imgui.h>

namespace Sampo
{
	Input::~Input()
	{
		for (int i = 0; i < myInputDevices.size(); i++)
			delete myInputDevices[i];
	}

	bool Input::Init()
	{
		InputDevice* mouse = AddInputDevice(new Mouse());
		m_Mouse = static_cast<Mouse*>(mouse);

		if (!m_Mouse)
			return false;

		return true;
	}

	InputDevice* Input::AddInputDevice(InputDevice* anInputDevice)
	{
		if (!anInputDevice->InitDevice())
		{
			delete anInputDevice;
			return nullptr;
		}
		
		return myInputDevices.emplace_back(anInputDevice);
	}

	int Input::GetFirstInputDeviceIndexByType(InputType anInputType) const
	{
		if (myInputDevices.empty())
			return -1;

		for (int i = 0; i < myInputDevices.size(); i++)
		{
			const InputDevice* inputDevice = myInputDevices[i];
			if (inputDevice->GetInputType() == anInputType)
				return i;
		}
		
		return -1;
	}

	const InputDevice* Input::GetInputDevice(uint32 anInputDeviceIndex) const
	{
		SAMPO_ASSERT(anInputDeviceIndex < myInputDevices.size());
		return myInputDevices[anInputDeviceIndex];
	}

	std::vector<const InputDevice*> Input::GetInputDevicesByUserIndex(int anUserIndex) const
	{
		std::vector<const InputDevice*> foundDevices;

		for (const InputDevice* device : myInputDevices)
		{
			if (device->GetUserIndex() != anUserIndex)
				continue;

			foundDevices.emplace_back(device);
		}
		return foundDevices;
	}

	std::vector<const InputDevice*> Input::GetAllInputDevicesOfTypeInputType(InputType anInputType) const
	{
		std::vector<const InputDevice*> foundDevices;

		for (const InputDevice* device : myInputDevices)
		{
			if (device->GetInputType() != anInputType)
				continue;

			foundDevices.emplace_back(device);
		}
		return foundDevices;
	}

	void Input::OnMouseEvent(Event& aMouseEvent)
	{
		SAMPO_ASSERT(m_Mouse);

		if (!aMouseEvent.IsInCategory(EventCategory::EventInput))
			return;

		m_Mouse->OnMouseEvent(aMouseEvent);
	}

	void Input::ImGuiDebug()
	{
		if (ImGui::TreeNode("Input"))
		{
			ImGui::Text("Connected devices: %d", myInputDevices.size());

			if (ImGui::CollapsingHeader("Mouse", ImGuiTreeNodeFlags_None))
			{
				const bool mousePresent = m_Mouse && m_Mouse->IsPresent();
				ImGui::Text("Present: [%s]", mousePresent ? "Enabled" : "Disconnected");
				if (mousePresent)
				{
					const MouseState& mouseState = m_Mouse->GetMouseState();
					if (mouseState.m_Enabled)
					{
						ImGui::Text("Position: %0.f, %0.f", mouseState.m_Position.x, mouseState.m_Position.y);
						ImGui::Text("Scroll: %0.f, %0.f", mouseState.m_ScrollOffset.x, mouseState.m_ScrollOffset.y);

						static ImGuiTableFlags flags = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_Hideable;

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
								ImGui::Text("%d", mouseState.m_Pressed[i]);
							}

							ImGui::EndTable();
						}
					}
				}
			}
			ImGui::TreePop();
		}
	}
}
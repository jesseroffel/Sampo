#include "sampo_pch.hpp"
#include "sampo/input/input.hpp"

#include "sampo/input/keyboard.hpp"
#include "sampo/input/mouse.hpp"

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

		InputDevice* keyboard = AddInputDevice(new Keyboard());
		m_Keyboard = static_cast<Keyboard*>(keyboard);
		if (!m_Keyboard)
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

	void Input::OnKeyboardEvent(Event& aKeyboardEvent)
	{
		SAMPO_ASSERT(m_Keyboard);

		if (!aKeyboardEvent.IsInCategory(EventCategory::EventInput))
			return;

		m_Keyboard->OnKeyboardEvent(aKeyboardEvent);
	}

	void Input::ImGuiDebug()
	{
		if (ImGui::TreeNode("Input"))
		{
			ImGui::Text("Connected devices: %d", myInputDevices.size());

			if (ImGui::CollapsingHeader("Mouse", ImGuiTreeNodeFlags_None))
			{
				if (m_Mouse)
					m_Mouse->ImGuiDebug();
			}

			if (ImGui::CollapsingHeader("Keyboard", ImGuiTreeNodeFlags_None))
			{
				if (m_Keyboard)
					m_Keyboard->ImGuiDebug();
			}
			ImGui::TreePop();
		}
	}
}
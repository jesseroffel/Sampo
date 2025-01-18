#include "sampo_pch.hpp"
#include "input.hpp"

#include "input_device.hpp"
#include "gamepad.hpp"
#include "keyboard.hpp"
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
		m_Mouse = static_cast<Mouse*>(AddInputDevice(new Mouse()));
		if (!m_Mouse)
			return false;

		m_Keyboard = static_cast<Keyboard*>(AddInputDevice(new Keyboard()));
		if (!m_Keyboard)
			return false;

		return true;
	}

	void Input::Update()
	{
		PollDevices();
	}

	InputDevice* Input::AddInputDevice(InputDevice* anInputDevice)
	{
		if (!anInputDevice->InitDevice())
		{
			delete anInputDevice;
			return nullptr;
		}
		m_DevicesHandled++;
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

		if (!aMouseEvent.IsInCategory(EventCategory::EventMouse))
			return;

		m_Mouse->OnMouseEvent(aMouseEvent);
	}

	void Input::OnKeyboardEvent(Event& aKeyboardEvent)
	{
		SAMPO_ASSERT(m_Keyboard);

		if (!aKeyboardEvent.IsInCategory(EventCategory::EventKeyboard))
			return;

		m_Keyboard->OnKeyboardEvent(aKeyboardEvent);
	}

	void Input::OnGamepadEvent(Event& aGamepadEvent)
	{
		if (!aGamepadEvent.IsInCategory(EventCategory::EventGamepad))
			return;

		const EventType eventType = aGamepadEvent.GetEventType();
		const int platformId = Gamepad::GetPlatformIdFromEvent(aGamepadEvent);
		SAMPO_ASSERT(platformId != -1);

		if (eventType == EventType::JoystickConnected)
		{
			AddInputDevice(new Gamepad(platformId));
		}
		else if (eventType == EventType::JoystickDisconnected)
		{
			const Gamepad* foundGamepad = GetGamepadByPlatformId(platformId);
			SAMPO_ASSERT(foundGamepad);

			myInputDevices.erase(std::remove_if(myInputDevices.begin(), myInputDevices.end(), [&platformId](const InputDevice* aDevice)
			{ 
				if (aDevice->GetInputType() != InputType::kGamepad)
					return false;

				return static_cast<const Gamepad*>(aDevice)->GetPlatformId() == platformId;
			}));
		}
	}

	void Input::PollDevices()
	{
		for (InputDevice* device : myInputDevices)
		{
			if (!device->GetRequiresPolling())
				continue;

			device->PollDevice();
		}
	}

	const Gamepad* Input::GetGamepadByPlatformId(int aGamepadId) const
	{
		for (const InputDevice* device : myInputDevices)
		{
			if (device->GetInputType() != InputType::kGamepad)
				continue;

			const Gamepad* gamepad = static_cast<const Gamepad*>(device);
			if (gamepad->GetPlatformId() == aGamepadId)
				return gamepad;
		}
		return nullptr;
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

			if (ImGui::CollapsingHeader("Gamepad", ImGuiTreeNodeFlags_None))
			{
				for (InputDevice* device : myInputDevices)
				{
					if (device->GetInputType() == InputType::kMouse || device->GetInputType() == InputType::kKeyboard)
						continue;

					Gamepad* gamepad = static_cast<Gamepad*>(device);
					gamepad->ImGuiDebug();
				}
			}
			ImGui::TreePop();
		}
	}
}
#pragma once
#include "input_types.hpp"

namespace Sampo
{
	class Event;
	class Gamepad;
	class InputDevice;
	class Keyboard;
	class Mouse;

	// Input container class to retrieve input data from
	class Input
	{
	public:
		Input() = default;
		virtual ~Input();

		virtual bool Init();
		virtual void Update();

		virtual InputDevice* AddInputDevice(InputDevice* anInputDevice);

		int GetFirstInputDeviceIndexByType(InputType anInputType) const;
		const InputDevice* GetInputDevice(uint32 anInputDeviceIndex) const;
		std::vector<const InputDevice*> GetInputDevicesByUserIndex(int anUserIndex) const;
		std::vector<const InputDevice*> GetAllInputDevicesOfTypeInputType(InputType anInputType) const;
		const Gamepad* GetGamepadByPlatformId(int aGamepadId) const;

		void OnMouseEvent(Event& aMouseEvent);
		void OnKeyboardEvent(Event& aKeyboardEvent);
		void OnGamepadEvent(Event& aGamepadEvent);

		virtual void ImGuiDebug();

	protected:
		void PollDevices();
		virtual void DiscoverConnectedGamepads() {};

		std::vector<InputDevice*> myInputDevices;

		Mouse* m_Mouse{ nullptr };
		Keyboard* m_Keyboard{ nullptr };
		uint32 m_DevicesHandled{ 0 };
	};
}
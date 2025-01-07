#pragma once
#include "input_device.hpp"

namespace Sampo
{
	class Event;
	class Keyboard;
	class Mouse;

	// Input container class to retrieve input data from
	class Input
	{
	public:
		Input() = default;
		~Input();

		virtual bool Init();

		virtual InputDevice* AddInputDevice(InputDevice* anInputDevice);

		int GetFirstInputDeviceIndexByType(InputType anInputType) const;
		const InputDevice* GetInputDevice(uint32 anInputDeviceIndex) const;
		std::vector<const InputDevice*> GetInputDevicesByUserIndex(int anUserIndex) const;
		std::vector<const InputDevice*> GetAllInputDevicesOfTypeInputType(InputType anInputType) const;

		void OnMouseEvent(Event& aMouseEvent);
		void OnKeyboardEvent(Event& aKeyboardEvent);

		virtual void ImGuiDebug();

	protected:
		Mouse* m_Mouse{ nullptr };
		Keyboard* m_Keyboard{ nullptr };

		std::vector<InputDevice*> myInputDevices;
	};
}
#pragma once
#include "input_device.hpp"

#include "mouse.hpp"

namespace Sampo
{
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

		virtual void ImGuiDebug();

	protected:
		Mouse* m_Mouse{ nullptr };
		std::vector<InputDevice*> myInputDevices;
	};
}
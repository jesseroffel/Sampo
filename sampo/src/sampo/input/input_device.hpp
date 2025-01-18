#pragma once
#include "input_types.hpp"

namespace Sampo
{
	struct DeviceInformation
	{
		std::string m_DeviceName{ "Unknown device name" };
		std::string m_DeviceGUID{ "00000000-0000-0000-0000-000000000000" };
	};
	class InputDevice
	{
	public:
		InputDevice(InputType anInputType, int anUserIndex = 0)
			: m_InputType(anInputType)
			, m_UserIndex(anUserIndex){}

		virtual bool InitDevice() { return true; };

		virtual void PollDevice() {};

		const std::string_view GetDeviceName() const { return m_DeviceInformation.m_DeviceName; }
		const std::string_view GetDeviceUID() const { return m_DeviceInformation.m_DeviceGUID; }
		
		InputType GetInputType() const { return m_InputType; }
		int GetUserIndex() const { return m_UserIndex; }
		bool GetRequiresPolling() const { return m_RequiresPolling; }

		virtual void ImGuiDebug() {};
	protected:
		DeviceInformation m_DeviceInformation;

		InputType m_InputType{ InputType::kUnknown };
		int m_UserIndex{ -1 };
		bool m_RequiresPolling{ false };
	};
}
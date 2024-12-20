#pragma once
#include "input_types.hpp"

namespace Sampo
{
	class InputDevice
	{
	public:
		InputDevice(InputType anInputType, int anUserIndex = 0)
			: m_InputType(anInputType)
			, m_UserIndex(anUserIndex){}

		virtual bool InitDevice() { return true; };

		InputType GetInputType() const { return m_InputType; }
		int GetUserIndex() const { return m_UserIndex; }
	private:
		InputType m_InputType{ InputType::kUnknown };
		int m_UserIndex{ -1 };
	};
}
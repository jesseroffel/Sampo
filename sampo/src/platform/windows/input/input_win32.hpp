#pragma once
#include "sampo/input/input.hpp"

namespace Sampo
{
	class Win32Input final : public Input
	{
	public:
		Win32Input() = default;
		~Win32Input() = default;
		
		bool Init() override;
	private:
		void DiscoverConnectedGamepads() override;
	};
}
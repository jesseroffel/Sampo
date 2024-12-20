#pragma once
#include "sampo/graphics/window.hpp"

#include "sampo/core/platform_types.hpp"
#include "sampo/input/input.hpp"

namespace Sampo
{
	class Win32Platform
	{
	public:
		Win32Platform();
		~Win32Platform();

		bool Init(const std::string& aWindowName);
		void Update();
		void Shutdown();

		Window* GetWindow() const;
		Input& GetInput() const { return *m_Input; }

		void ImGuiDebug();

	private:
		Window* m_Window{ nullptr };
		Input* m_Input{ nullptr };

		PlatformType myPlatformType{ PlatformType::kPC };
		PlatformDevice myPlatformDevice{ PlatformDevice::kWindows };
	};
}
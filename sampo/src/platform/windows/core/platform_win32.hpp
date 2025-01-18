#pragma once
#include "sampo/graphics/window.hpp"

#include "sampo/core/platform_types.hpp"

namespace Sampo
{
	class Input;
	class Win32Window;

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
		Win32Window* m_Window{ nullptr };
		Input* m_Input{ nullptr };

		PlatformType myPlatformType{ PlatformType::kPC };
		PlatformDevice myPlatformDevice{ PlatformDevice::kWindows };
	};
}
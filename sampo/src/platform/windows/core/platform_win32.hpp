#pragma once
#include "sampo/graphics/window.hpp"

#include "sampo/core/platform_types.hpp"
#include "sampo/core/core_parameters.hpp"

namespace Sampo
{
	class Input;
	class Win32Window;
	class AudioAPI;

	class Win32Platform
	{
	public:
		Win32Platform();
		~Win32Platform();

		bool Init(StartParams& aStartParams);
		void Update();
		void Shutdown();

		Window* GetWindow() const { return m_Window;}
		Input& GetInput() const { return *m_Input; }
		AudioAPI* GetAudio() const { return m_AudioAPI; }

		float GetTime() const;

	#ifdef SAMPO_IMGUI_ENABLED
		virtual void ImGuiDebug();
	#endif // SAMPO_IMGUI_ENABLED

	private:
		Win32Window* m_Window{ nullptr };
		Input* m_Input{ nullptr };
		AudioAPI* m_AudioAPI{ nullptr };

		PlatformType myPlatformType{ PlatformType::kPC };
		PlatformDevice myPlatformDevice{ PlatformDevice::kWindows };
	};
}
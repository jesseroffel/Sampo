#pragma once
#include "sampo/core/core_parameters.hpp"

namespace Sampo
{
	class SoundEffect;

	class AudioDevice
	{
	public:
		virtual ~AudioDevice() = default;

		virtual bool Init(AudioConfigParams& anAudioConfigParams) = 0;
		virtual void Update() = 0;
		virtual void Shutdown() = 0;

		virtual bool Play(std::shared_ptr<Sampo::SoundEffect> aSoundEffect) = 0;
		virtual void Stop(std::shared_ptr<Sampo::SoundEffect> aSoundEffect) = 0;

	#ifdef SAMPO_IMGUI_ENABLED
		virtual void ImGuiDebug() = 0;
	#endif // SAMPO_IMGUI_ENABLED
	protected:

		uint32 m_SoundInstanceCount{ 0u };
		bool m_Initialized{ false };
	};
}
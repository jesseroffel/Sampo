#pragma once

#include "audio_device.hpp"

namespace Sampo
{
	class SoundEffect;

	class SoundEffectInstance
	{
	public:
		SoundEffectInstance(std::shared_ptr<SoundEffect> aSoundEffect)
			: m_SoundEffect(aSoundEffect)
		{
		}

		virtual ~SoundEffectInstance() = default;

		virtual bool Init(AudioDevice& anAudioDevice) = 0;
		virtual bool Play() = 0;
		virtual bool Stop() = 0;

		virtual bool IsReady() = 0;
		virtual bool IsAtEnd() = 0;

		const SoundEffect* GetSoundEffect() const { return m_SoundEffect.get(); }

		uint32 m_InstanceID{ uint32_max }; // SAMPO_TODO: Protected UUID 
		bool m_IsPlaying{ false };
	protected:
		std::shared_ptr<SoundEffect> m_SoundEffect{ nullptr };
		bool m_IsInitialized{ true };
	};
}
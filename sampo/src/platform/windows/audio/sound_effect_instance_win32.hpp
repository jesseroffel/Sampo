#pragma once
#include "sampo/audio/sound_effect_instance.hpp"

#include <miniaudio.h>

namespace Sampo
{
	class Win32SoundEffectInstance : public SoundEffectInstance
	{
	public:
		Win32SoundEffectInstance(std::shared_ptr<SoundEffect> aSoundEffect);
		virtual ~Win32SoundEffectInstance();

		virtual bool Init(AudioDevice& anAudioDevice);
		virtual bool Play();
		virtual bool Stop();

		virtual bool IsReady();
		virtual bool IsAtEnd();

	protected:
		ma_sound m_maSound{};
	};
}
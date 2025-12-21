#pragma once
#include "sampo/audio/sound_library.hpp"

namespace Sampo
{
	class Win32SoundLibrary : public SoundLibrary
	{
	public:
		Win32SoundLibrary() = default;
		virtual ~Win32SoundLibrary() = default;

		virtual void OnSoundLoaded(void* aCallbackData) override;
	};
}
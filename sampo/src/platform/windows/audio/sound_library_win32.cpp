#include "sampo_pch.hpp"
#include "sound_library_win32.hpp"

#include "sound_effect_win32.hpp"

#include <miniaudio.h>

namespace Sampo
{
	void Win32SoundLibrary::OnSoundLoaded(void* aCallbackData)
	{
		MAAsyncLoadFinished* maASyncNotification = static_cast<MAAsyncLoadFinished*>(aCallbackData);

		const uint32* soundID = static_cast<uint32*>(maASyncNotification->m_CallbackUserData);
		if (!soundID)
			return;

		for (auto it = m_SoundEffects.begin(); it != m_SoundEffects.end();)
		{
			SoundEffect* soundEffect = it->second.get();

			if (soundEffect->GetSoundEffectID() != *soundID)
			{
				it++;
				continue;
			}

			soundEffect->SetIsLoaded();

			if (soundEffect->IsOneOff())
				m_SoundEffects.erase(it);

			break;
		}
	}
}
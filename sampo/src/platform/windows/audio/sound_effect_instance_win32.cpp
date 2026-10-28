#include "sampo_pch.hpp"
#include "sound_effect_instance_win32.hpp"

#include "audio_device_win32.hpp"
#include "sound_effect_win32.hpp"

#include "sampo/audio/audio_api.hpp"

namespace Sampo
{
	Win32SoundEffectInstance::Win32SoundEffectInstance(std::shared_ptr<SoundEffect> aSoundEffect)
		: SoundEffectInstance(aSoundEffect)
	{
	}

	Win32SoundEffectInstance::~Win32SoundEffectInstance()
	{
		if (!m_IsInitialized)
			return;

		Stop();
		ma_sound_uninit(&m_maSound);
		//ma_audio_buffer_ref_uninit(&m_maAudioBufferRef);
	}

	bool Win32SoundEffectInstance::Init(AudioDevice& anAudioDevice)
	{
		if (m_IsInitialized)
			return true;

		Win32SoundEffect* soundEffect = static_cast<Win32SoundEffect*>(m_SoundEffect.get());
		//if (!soundEffect->GetAudioBuffer(m_maAudioBufferRef))
		//	return false;

		Win32AudioDevice& audioDevice = static_cast<Win32AudioDevice&>(anAudioDevice);
		const uint32 soundEffectFlags = soundEffect->GetLoadingFlags();
		const ma_result result = ma_sound_init_from_file(audioDevice.GetMAEngine(), soundEffect->GetFilepath().c_str(), soundEffectFlags, nullptr, nullptr, &m_maSound);
		//const ma_result result = ma_sound_init_from_data_source(audioDevice.GetMAEngine(), soundEffect->GetSoundDataSource(), soundEffectFlags, nullptr, &m_maSound);
		//const ma_result result = ma_sound_init_from_data_source(audioDevice.GetMAEngine(), static_cast<ma_data_source*>(&m_maAudioBufferRef), soundEffectFlags, nullptr, &m_maSound);
		if (result != MA_SUCCESS)
		{
			SAMPO_CORE_ERROR("ma_sound_init_from_data_source error ({0}) with flags {1} when loading path: {2}.", result, soundEffectFlags, soundEffect->GetFilepath());
			return false;
		}

		if (soundEffect->m_SoundEffectParams.m_AdjustedVolume != 100)
		{
			const float adjustedVolume = static_cast<float>(soundEffect->m_SoundEffectParams.m_AdjustedVolume) / 100.0f;
			ma_sound_set_volume(&m_maSound, adjustedVolume);
		}

		ma_sound_set_end_callback(&m_maSound, [](void* aSoundUserData, ma_sound* aMASound) {
			static_cast<Win32AudioDevice*>(Sound::GetAudioDevice())->OnSoundAtEnd(aSoundUserData, aMASound);
		}, static_cast<void*>(&m_InstanceID));

		m_IsInitialized = true;
		return true;
	}

	bool Win32SoundEffectInstance::Play()
	{
		if (m_IsPlaying)
		{
			const ma_result rewindresult = ma_sound_seek_to_pcm_frame(&m_maSound, 0);
			if (rewindresult != MA_SUCCESS)
			{
				SAMPO_CORE_ERROR("ma_sound_start error ({0}): when playing {1}.", rewindresult, m_SoundEffect->GetFilepath().c_str());
				return false;
			}
		}

		const ma_result startResult = ma_sound_start(&m_maSound);
		if (startResult != MA_SUCCESS)
		{
			SAMPO_CORE_ERROR("ma_sound_start error ({0}): when playing {1}.", startResult, m_SoundEffect->GetFilepath().c_str());
			return false;
		}

		m_IsPlaying = true;
		return true;
	}

	bool Win32SoundEffectInstance::Stop()
	{
		if (!m_IsPlaying)
			return true;

		ma_sound_stop(&m_maSound);
		m_IsPlaying = false;
		return true;
	}

	bool Win32SoundEffectInstance::IsReady()
	{
		return m_IsInitialized && (m_SoundEffect && m_SoundEffect->IsLoaded());
	}

	bool Win32SoundEffectInstance::IsAtEnd()
	{
		return !m_SoundEffect->m_SoundEffectParams.m_Looping && ma_sound_at_end(&m_maSound);
	}
}
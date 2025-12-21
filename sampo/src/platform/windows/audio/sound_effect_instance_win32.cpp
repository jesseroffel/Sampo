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
		Stop();

		if (!m_IsInitialized)
			return;

		ma_sound_uninit(&m_maSound);
	}

	bool Win32SoundEffectInstance::Init(AudioDevice& anAudioDevice)
	{
		Win32AudioDevice& audioDevice = static_cast<Win32AudioDevice&>(anAudioDevice);
		Win32SoundEffect* soundEffect = static_cast<Win32SoundEffect*>(m_SoundEffect.get());

		const auto endCallback = [](void* aSoundUserData, ma_sound* aMASound) {
			static_cast<Win32AudioDevice*>(Sound::GetAudioDevice())->OnSoundAtEnd(aSoundUserData, aMASound);
		};

 		ma_sound_config soundInstanceConfig = soundEffect->GetSoundInstanceConfig();
		soundInstanceConfig.endCallback = endCallback;
		soundInstanceConfig.pEndCallbackUserData = static_cast<void*>(&m_InstanceID);

		ma_resource_manager_data_source_config dataResourceConfig = soundEffect->GetDataResourceConfig();

		//const ma_result result = ma_sound_init_copy(audioDevice.GetMAEngine(), soundEffect->GetLoadedSound(), soundInstanceConfig.flags, nullptr, &m_maSound);
		const ma_result result = ma_sound_init_ex(audioDevice.GetMAEngine(), &soundInstanceConfig, &m_maSound);
		//const ma_result result = ma_sound_init_from_data_source(audioDevice.GetMAEngine(), soundEffect->GetSoundDataSource(), dataResourceConfig.flags, nullptr, &m_maSound);
		if (result != MA_SUCCESS)
		{
			//SAMPO_CORE_ERROR("ma_sound_init_from_data_source error ({0}) with flags {1} when loading path: {2}.", result, soundInstanceConfig.flags, soundInstanceConfig.pFilePath);
			SAMPO_CORE_ERROR("ma_sound_init_from_data_source error ({0}) with flags {1} when loading path: {2}.", result, dataResourceConfig.flags, soundEffect->GetFilepath().c_str());
			return false;
		}

		if (soundEffect->m_SoundEffectParams.m_AdjustedVolume != 100)
		{
			const float adjustedVolume = static_cast<float>(soundEffect->m_SoundEffectParams.m_AdjustedVolume) / 100.0f;
			ma_sound_set_volume(&m_maSound, adjustedVolume);
		}

		m_IsInitialized = true;
		return true;
	}

	bool Win32SoundEffectInstance::Play()
	{
		const ma_result result = ma_sound_start(&m_maSound);
		if (result != MA_SUCCESS)
		{
			SAMPO_CORE_ERROR("ma_sound_start error ({0}): when playing {1}.", result, m_SoundEffect->GetFilepath().c_str());
			return false;
		}

		m_IsPlaying = true;
		return true;
	}

	bool Win32SoundEffectInstance::Stop()
	{
		const ma_result result = ma_sound_stop(&m_maSound);
		if (result != MA_SUCCESS)
		{
			SAMPO_CORE_ERROR("ma_sound_stop error ({0}): when playing {1}.", result, m_SoundEffect->GetFilepath().c_str());
			return false;
		}

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
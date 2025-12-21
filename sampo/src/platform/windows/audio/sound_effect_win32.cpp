#include "sampo_pch.hpp"
#include "sound_effect_win32.hpp"

#include "sampo/audio/audio_api.hpp"

#include "audio_device_win32.hpp"

#include <miniaudio.h>

namespace Sampo
{
	Win32SoundEffect::Win32SoundEffect(const std::string& aFilepath, const SoundEffectParams& aSoundEffectParams)
		: SoundEffect(aFilepath, aSoundEffectParams)
	{
		SetupDataSourceSoundConfig();
		SetupSoundInstanceConfig();
	}

	Win32SoundEffect::~Win32SoundEffect()
	{
		if (!m_IsLoaded)
			return;

		ma_sound_uninit(&m_maSoundEffect);
		ma_resource_manager_data_source_uninit(&m_maDataSource);
	}

	bool Win32SoundEffect::Play()
	{
		return Sound::Play(this);
	}

	bool Win32SoundEffect::Stop()
	{
		return Sound::Stop(this);
	}

	void Win32SoundEffect::SetIsLoaded()
	{
		SoundEffect::SetIsLoaded();

		Win32AudioDevice* audioDevice = static_cast<Win32AudioDevice*>(Sound::GetAudioDevice());

		const ma_result result = ma_sound_init_ex(audioDevice->GetMAEngine(), &m_maSoundInstanceConfig, &m_maSoundEffect);
		if (result != MA_SUCCESS)
		{
			SAMPO_CORE_ERROR("ma_sound_init_ex error ({0}) with flags {1} when loading path: {2}.", result, m_maSoundInstanceConfig.flags, m_maSoundInstanceConfig.pFilePath);
			return;
		}
	}

	float Win32SoundEffect::GetSoundEffectLength() const
	{
		//const ma_result readFramesResult = ma_data_source_read_pcm_frames();
		return 0.f;
	}

	bool Win32SoundEffect::Load()
	{
		if (m_IsLoaded)
			return true;

		LoadDataSourceSound();
		return true;
	}


	void Win32SoundEffect::SetupSoundInstanceConfig()
	{
		Win32AudioDevice* audioDevice = static_cast<Win32AudioDevice*>(Sound::GetAudioDevice());
		SAMPO_ASSERT_MSG(audioDevice, "No valid Audio Device is active!");

		m_maSoundInstanceConfig = ma_sound_config_init_2(audioDevice->GetMAEngine());
		m_maSoundInstanceConfig.pDataSource = &m_maDataSource;
		//m_maSoundInstanceConfig.pFilePath = aFilepath.c_str();
		m_maSoundInstanceConfig.flags = GetLoadingFlags(MASoundType::Raw);

// 		const auto soundLoadedCallback = [](ma_async_notification* pNotification) {
// 			Sound::GetSoundLibrary()->OnSoundLoaded(pNotification);
// 		};
// 
// 		m_loadFinished.m_Callbacks.onSignal = soundLoadedCallback;
// 		m_loadFinished.m_CallbackUserData = static_cast<void*>(&m_SoundEffectID);
// 
// 		m_maSoundInstanceConfig.initNotifications = ma_resource_manager_pipeline_notifications_init();
// 		m_maSoundInstanceConfig.initNotifications.done.pNotification = &m_loadFinished;
	}

	bool Win32SoundEffect::LoadDataSourceSound()
	{
		Win32AudioDevice* audioDevice = static_cast<Win32AudioDevice*>(Sound::GetAudioDevice());
		SAMPO_ASSERT_MSG(audioDevice, "No valid Audio Device is active!");

		const ma_result result = ma_resource_manager_data_source_init_ex(audioDevice->GetMAEngine()->pResourceManager, &m_maDataSourceConfig, &m_maDataSource);
		if (result != MA_SUCCESS)
		{
			SAMPO_CORE_ERROR("ma_sound_init_from_file error ({0}) with flags {1} when loading path: {2}.", result, m_maSoundInstanceConfig.flags, m_maSoundInstanceConfig.pFilePath);
			return false;
		}

		return true;
	}

	void Win32SoundEffect::SetupDataSourceSoundConfig()
	{
		Win32AudioDevice* audioDevice = static_cast<Win32AudioDevice*>(Sound::GetAudioDevice());
		SAMPO_ASSERT_MSG(audioDevice, "No valid Audio Device is active!");

		m_maDataSourceConfig = ma_resource_manager_data_source_config_init();
		m_maDataSourceConfig.pFilePath = m_Filepath.c_str();
		m_maDataSourceConfig.flags = GetLoadingFlags(MASoundType::DataSource);

		const auto soundLoadedCallback = [](ma_async_notification* pNotification) {
			Sound::GetSoundLibrary()->OnSoundLoaded(pNotification);
		};

		m_loadFinished.m_Callbacks.onSignal = soundLoadedCallback;
		m_loadFinished.m_CallbackUserData = static_cast<void*>(&m_SoundEffectID);

		m_maNotifications = ma_resource_manager_pipeline_notifications_init();
		m_maNotifications.done.pNotification = &m_loadFinished;

		m_maDataSourceConfig.pNotifications = &m_maNotifications;
	}

	uint32 Win32SoundEffect::GetLoadingFlags(MASoundType aSoundType) const
	{
		if (aSoundType == MASoundType::Invalid)
		{
			SAMPO_CORE_ERROR("Unable to retrieve miniaudio loading flags as an incorrect sound type was provided: {0}.", static_cast<uint32>(aSoundType));
			return 0u;
		}

		uint32 m_LoadingFlags{ 0u };

		if (m_SoundEffectParams.m_DecodeSound)
			m_LoadingFlags += aSoundType == MASoundType::Raw ? MA_SOUND_FLAG_DECODE : MA_RESOURCE_MANAGER_DATA_SOURCE_FLAG_DECODE;

		if (m_SoundEffectParams.m_AsyncLoad)
			m_LoadingFlags += aSoundType == MASoundType::Raw ? MA_SOUND_FLAG_ASYNC : MA_RESOURCE_MANAGER_DATA_SOURCE_FLAG_ASYNC;

// 		if (m_SoundEffectParams.m_Looping)
// 			m_LoadingFlags += aSoundType == MASoundType::Raw ? MA_SOUND_FLAG_LOOPING : MA_RESOURCE_MANAGER_DATA_SOURCE_FLAG_LOOPING;

// 		if (!m_SoundEffectParams.m_EnableSpatialization && aSoundType == MASoundType::Raw)
// 			m_LoadingFlags += MA_SOUND_FLAG_NO_SPATIALIZATION;

		if (m_SoundEffectParams.m_StreamFile /*&& audio size > 2 sec*/)
			m_LoadingFlags += aSoundType == MASoundType::Raw ? MA_SOUND_FLAG_STREAM : MA_RESOURCE_MANAGER_DATA_SOURCE_FLAG_STREAM;

		return m_LoadingFlags;
	}
}
#include "sampo_pch.hpp"
#include "audio_device_win32.hpp"

#include "sound_effect_win32.hpp"

#include <imgui.h>

namespace Sampo
{
	bool Win32AudioDevice::Init(AudioConfigParams& anAudioConfigParams)
	{
		// Audio device config
		const ma_device_type deviceType = ma_device_type_playback; // Only allow audio output, input disabled.
		ma_device_config deviceConfig = ma_device_config_init(deviceType);
		deviceConfig.playback.format = ma_format_f32;//static_cast<ma_format>(anAudioConfigParams.m_PlaybackFormat);
		deviceConfig.playback.channels = 2;//anAudioConfigParams.m_Channels;
		deviceConfig.sampleRate = 48000;//anAudioConfigParams.m_SampleRate;

		const ma_result deviceInitResult = ma_device_init(nullptr, &deviceConfig, &m_maDevice);
		if (deviceInitResult != MA_SUCCESS)
		{
			SAMPO_CORE_ERROR("Failed to init audio API call ma_device_init: {0}", deviceInitResult);
			return false;
		}

		ma_resource_manager_config resourceManagerConfig = ma_resource_manager_config_init();
		// Set decoding format/channels/sample rate to be the same across all loaded files for now.
		resourceManagerConfig.decodedFormat = ma_format_f32;//m_maDevice.playback.format;
		resourceManagerConfig.decodedChannels = 2;//anAudioConfigParams.m_Channels
		resourceManagerConfig.decodedSampleRate = 48000;//m_maDevice.sampleRate;
		resourceManagerConfig.jobThreadCount = anAudioConfigParams.m_AudioThreads; // SAMPO_TODO: Integrate miniaudio job tasks into sampo jobs tasks.

		const ma_result resourceManagerInitResult = ma_resource_manager_init(&resourceManagerConfig, &m_maResourceManager);
		if (resourceManagerInitResult != MA_SUCCESS)
		{
			ma_device_uninit(&m_maDevice);
			SAMPO_CORE_ERROR("Failed to init audio API call ma_resource_manager_init: {0}", deviceInitResult);
			return false;
		}

		ma_engine_config engineConfig = ma_engine_config_init();
		engineConfig.pResourceManager = &m_maResourceManager;

		const ma_result engineInitResult = ma_engine_init(&engineConfig, &m_maEngine);
		if (engineInitResult != MA_SUCCESS)
		{
			SAMPO_CORE_ERROR("Failed to init audio API call ma_engine_init: {0}", engineInitResult);
			return false;
		}

		m_Initialized = true;
		return true;
	}

	void Win32AudioDevice::Update()
	{
		if (m_QueuedSoundEffectInstances.empty())
			return;

		for (auto it = m_QueuedSoundEffectInstances.begin(); it != m_QueuedSoundEffectInstances.end();)
		{
			Win32SoundEffectInstance* soundEffectInstance = it->get();
			if (!soundEffectInstance->IsReady())
			{
				it++;
				continue;
			}

			AddActiveInstance(*it);
			it = m_QueuedSoundEffectInstances.erase(it);
		}
	}

	void Win32AudioDevice::Shutdown()
	{
		if (!m_Initialized)
			return;

		ma_device_stop(&m_maDevice);
		ma_device_uninit(&m_maDevice);
	}

	bool Win32AudioDevice::Play(std::shared_ptr<SoundEffect> aSoundEffect)
	{
		std::shared_ptr<Win32SoundEffectInstance> soundEffectInstance = CreateInstance(aSoundEffect);

		if (!aSoundEffect->IsLoaded())
		{
			aSoundEffect->Load();
			m_QueuedSoundEffectInstances.emplace_back(soundEffectInstance);
			return true;
		}

		return AddActiveInstance(soundEffectInstance);
	}

	void Win32AudioDevice::Stop(std::shared_ptr<Sampo::SoundEffect> aSoundEffect)
	{
		for (auto it = m_ActiveSoundEffectInstances.begin(); it != m_ActiveSoundEffectInstances.end(); it++)
		{
			Win32SoundEffectInstance* instance = it->second.get();
			if (instance->GetSoundEffect()->GetSoundEffectID() != aSoundEffect->GetSoundEffectID())
				continue;

			instance->Stop();
		}
	}

	void Win32AudioDevice::OnSoundAtEnd(void* aSoundEffectData, ma_sound* aMASound)
	{
		const uint32* soundID = static_cast<uint32*>(aSoundEffectData);
		if (!soundID || !aMASound)
			return;

		auto foundEffect = m_ActiveSoundEffectInstances.find(*soundID);
		if (foundEffect == m_ActiveSoundEffectInstances.end())
			return;

		m_ActiveSoundEffectInstances.erase(foundEffect);
	}

	std::shared_ptr<Sampo::Win32SoundEffectInstance> Win32AudioDevice::CreateInstance(std::shared_ptr<SoundEffect> aSoundEffect)
	{
		std::shared_ptr<Win32SoundEffectInstance> instance = CreateShared<Win32SoundEffectInstance>(aSoundEffect);
		instance->m_InstanceID = m_SoundInstanceCount++;;
		return instance;
	}

	bool Win32AudioDevice::AddActiveInstance(std::shared_ptr<Win32SoundEffectInstance> aNewInstance)
	{
		if (!aNewInstance->Init(*this))
			return false;

		const auto activeSoundInstance = m_ActiveSoundEffectInstances.try_emplace(aNewInstance->m_InstanceID, aNewInstance);

		Win32SoundEffectInstance* instance = activeSoundInstance.first->second.get();
		return instance->Play();
	}

#ifdef SAMPO_IMGUI_ENABLED
	void Win32AudioDevice::ImGuiDebug()
	{
		if (ImGui::TreeNode("Audio Device"))
		{
			ImGui::Text("Total sound effect instances running: %u", m_ActiveSoundEffectInstances.size());
			for (auto it = m_ActiveSoundEffectInstances.begin(); it != m_ActiveSoundEffectInstances.end();)
			{
				SoundEffectInstance* soundEffectInstance = it->second.get();
				ImGui::PushID(soundEffectInstance->m_InstanceID);

				if (ImGui::Button("Stop instance"))
				{
					it = m_ActiveSoundEffectInstances.erase(it);
					ImGui::PopID();
					continue;
				}

				ImGui::Text("Sound ID: %u", soundEffectInstance->m_InstanceID);
				ImGui::Text("Path: %s", soundEffectInstance->GetSoundEffect()->GetFilepath().c_str());
				ImGui::Text("Is Playing: %u", soundEffectInstance->m_IsPlaying);

				ImGui::PopID();
				it++;
			}
			ImGui::TreePop();
		}
	}
#endif // SAMPO_IMGUI_ENABLED
}
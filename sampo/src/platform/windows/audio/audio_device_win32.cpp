#include "sampo_pch.hpp"
#include "audio_device_win32.hpp"

#include "sound_effect_win32.hpp"

#include <extras/decoders/libvorbis/miniaudio_libvorbis.h>
#include <imgui.h>

namespace Sampo
{
	bool Win32AudioDevice::Init(const AudioConfigParams& anAudioConfigParams)
	{
		ma_resource_manager_config resourceManagerConfig = ma_resource_manager_config_init();

		ma_decoding_backend_vtable* pCustomBackendVTables[] = { ma_decoding_backend_libvorbis };
		resourceManagerConfig.ppCustomDecodingBackendVTables = pCustomBackendVTables;
		resourceManagerConfig.customDecodingBackendCount =  sizeof(pCustomBackendVTables) / sizeof(pCustomBackendVTables[0]);
		resourceManagerConfig.pCustomDecodingBackendUserData = nullptr;

		const ma_result resourceManagerInit = ma_resource_manager_init(&resourceManagerConfig, &m_maResourceManager);
		if (resourceManagerInit != MA_SUCCESS)
		{
			SAMPO_CORE_ERROR("Audio API init call 'ma_resource_manager_init' failed with result code {0}", resourceManagerInit);
			return false;
		}

		ma_engine_config engineConfig = ma_engine_config_init();
		engineConfig.channels = anAudioConfigParams.m_Channels;
		engineConfig.sampleRate = anAudioConfigParams.m_SampleRate;
		engineConfig.pResourceManager = &m_maResourceManager;
		const ma_result engineInit = ma_engine_init(&engineConfig, &m_maEngine);
		if (engineInit != MA_SUCCESS)
		{
			SAMPO_CORE_ERROR("Audio API init call 'ma_engine_init' failed with result code {0}", engineInit);
			ma_resource_manager_uninit(&m_maResourceManager);
			return false;
		}

		m_AudioChannels = anAudioConfigParams.m_Channels;
		m_Initialized = true;
		return true;
	}

	void Win32AudioDevice::Update()
	{
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
		
		for(int i = static_cast<int>(m_SoundEffectInstancesAtEnd.size()) - 1; i >= 0; --i)
		{
			if (const auto foundEffectIter = m_ActiveSoundEffectInstances.find(m_SoundEffectInstancesAtEnd[i]); foundEffectIter != m_ActiveSoundEffectInstances.end())
				m_ActiveSoundEffectInstances.erase(foundEffectIter);

			m_SoundEffectInstancesAtEnd.pop_back();
		}
	}

	void Win32AudioDevice::Shutdown()
	{
		if (!m_Initialized)
			return;

		ma_engine_uninit(&m_maEngine);
		ma_resource_manager_uninit(&m_maResourceManager);
	}

	bool Win32AudioDevice::Play(std::shared_ptr<SoundEffect> aSoundEffect)
	{
		std::shared_ptr<Win32SoundEffectInstance> soundEffectInstance = CreateInstance(aSoundEffect);

		if (!aSoundEffect->IsLoaded())
		{
			aSoundEffect->Load(true);
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
			m_SoundEffectInstancesAtEnd.emplace_back(instance->m_InstanceID);
		}
	}

	void Win32AudioDevice::InitDecoderConfig(ma_decoder_config& outMaDecoderConfig)
	{
		outMaDecoderConfig = ma_decoder_config_init(ma_format_unknown, m_AudioChannels, m_maEngine.sampleRate);

		const ma_resource_manager_config& resourceManagerConfig = m_maResourceManager.config;
		outMaDecoderConfig.ppCustomBackendVTables = resourceManagerConfig.ppCustomDecodingBackendVTables;
		outMaDecoderConfig.customBackendCount = resourceManagerConfig.customDecodingBackendCount;
		outMaDecoderConfig.pCustomBackendUserData = resourceManagerConfig.pCustomDecodingBackendUserData;
	}

	void Win32AudioDevice::OnSoundAtEnd(void* aSoundEffectData, ma_sound* aMASound)
	{
		const uint32* soundID = static_cast<uint32*>(aSoundEffectData);
		if (!soundID || !aMASound)
			return;

		m_SoundEffectInstancesAtEnd.emplace_back(*soundID);
	}

	std::shared_ptr<Sampo::Win32SoundEffectInstance> Win32AudioDevice::CreateInstance(std::shared_ptr<SoundEffect> aSoundEffect)
	{
		std::shared_ptr<Win32SoundEffectInstance> instance = CreateShared<Win32SoundEffectInstance>(aSoundEffect);
		instance->m_InstanceID = m_SoundInstanceCount++;
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
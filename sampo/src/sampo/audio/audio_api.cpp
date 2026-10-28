#include "sampo_pch.hpp"
#include "audio_api.hpp"

#include "sampo/core/console_arguments.hpp"

#ifdef SAMPO_PLATFORM_WINDOWS
#include "platform/windows/audio/audio_api_win32.hpp"
#include "platform/windows/audio/audio_device_win32.hpp"
#include "platform/windows/audio/sound_library_win32.hpp"
#endif // SAMPO_PLATFORM_WINDOWS

#include <imgui.h>

namespace Sampo
{
	std::shared_ptr<SoundEffect> Sound::Create(const std::string& aFilepath, const SoundEffectParams& aSoundEffectParams)
	{
		return AudioAPI::GetInstance().CreateSoundEffect(aFilepath, aSoundEffectParams, false);
	}

	bool Sound::Play(const SoundEffect* aSoundEffect)
	{
		return AudioAPI::GetInstance().Play(aSoundEffect);
	}

	bool Sound::PlayOnce(const std::string& aFilepath, const SoundEffectParams& aSoundEffectParams)
	{
		return AudioAPI::GetInstance().PlayOnce(aFilepath, aSoundEffectParams);
	}

	bool Sound::Stop(const SoundEffect* aSoundEffect)
	{
		return AudioAPI::GetInstance().Stop(aSoundEffect);
	}

	AudioDevice* Sound::GetAudioDevice()
	{
		return AudioAPI::GetInstance().GetAudioDevice();
	}

	SoundLibrary* Sound::GetSoundLibrary()
	{
		return AudioAPI::GetInstance().GetSoundLibrary();
	}

	/////////////////////////////////////////

	AudioAPI* AudioAPI::s_Instance = nullptr;

	AudioAPI::AudioAPI()
	{
#ifdef SAMPO_PLATFORM_WINDOWS
		m_AudioDevice = new Win32AudioDevice();
		m_SoundLibrary = new Win32SoundLibrary();
#endif // SAMPO_PLATFORM_WINDOWS
	}

	AudioAPI* AudioAPI::Create()
	{
		SAMPO_ASSERT_MSG(!s_Instance, "AudioAPI is already initialized!");
		s_Instance = CreateInstance();
		return s_Instance;
	}

	AudioAPI& AudioAPI::GetInstance()
	{
		SAMPO_ASSERT_MSG(s_Instance, "AudioAPI has not been created!");
		return *s_Instance;
	}

	bool AudioAPI::Init()
	{
		if (m_AudioDevice)
		{
			AudioConfigParams configParams = CreateAudioConfigParams();
			m_AudioDevice->Init(configParams);
		}

		return true;
	}

	void AudioAPI::Update()
	{
		if (m_AudioDevice)
			m_AudioDevice->Update();
	}

	void AudioAPI::Shutdown()
	{
		SAMPO_ASSERT_MSG(s_Instance, "AudioAPI has already shut down!");

		if (m_AudioDevice)
		{
			m_AudioDevice->Shutdown();
			m_AudioDevice = nullptr;
		}

		delete s_Instance;
		s_Instance = nullptr;
	}

#ifdef SAMPO_IMGUI_ENABLED
	void AudioAPI::ImGuiDebug()
	{
		if (!m_AudioDevice || !m_SoundLibrary)
			return;

		if (ImGui::CollapsingHeader("Audio", ImGuiTreeNodeFlags_None))
		{
			m_AudioDevice->ImGuiDebug();
			m_SoundLibrary->ImGuiDebug();
		}
	}
#endif // SAMPO_IMGUI_ENABLED

	AudioAPI* AudioAPI::CreateInstance()
	{
#ifdef SAMPO_PLATFORM_WINDOWS
		s_Instance = new Win32AudioAPI();
#endif // SAMPO_PLATFORM_WINDOWS

		SAMPO_ASSERT_MSG(s_Instance, "Undefined platform, cannot create AudioAPI");
		return s_Instance;
	}

	AudioConfigParams AudioAPI::CreateAudioConfigParams()
	{
		ConsoleArguments& consoleArguments = ConsoleArguments::GetInstance();

		AudioConfigParams audioConfigParams;
		consoleArguments.GetIntValue("audio_channels", audioConfigParams.m_Channels);
		consoleArguments.GetIntValue("audio_sample_rate", audioConfigParams.m_SampleRate);

		return audioConfigParams;
	}

	const std::shared_ptr<SoundEffect> AudioAPI::CreateSoundEffect(const std::string& aFilepath, const SoundEffectParams& aSoundEffectParams, bool aPlayOnce)
	{
		SAMPO_ASSERT_MSG(m_SoundLibrary, "The sound library was not initialized correctly!");
		return m_SoundLibrary->Create(aFilepath, aSoundEffectParams, aPlayOnce);
	}

	bool AudioAPI::Play(const SoundEffect* aSoundEffect)
	{
		if (!m_SoundLibrary || !aSoundEffect)
			return false;

		if (!m_SoundLibrary->Exists(aSoundEffect->GetFilepath()))
			return false;

		std::shared_ptr<SoundEffect> soundEffect = m_SoundLibrary->Get(aSoundEffect->GetFilepath());
		return m_AudioDevice->Play(soundEffect);
	}

	bool AudioAPI::PlayOnce(const std::string& aFilepath, const SoundEffectParams& aSoundEffectParams)
	{
		std::shared_ptr<SoundEffect> soundEffect = nullptr;
		if (!m_SoundLibrary->Exists(aFilepath))
			soundEffect = CreateSoundEffect(aFilepath, aSoundEffectParams, true);
		else
			soundEffect = m_SoundLibrary->Get(aFilepath);

		return m_AudioDevice->Play(soundEffect);
	}

	bool AudioAPI::Stop(const SoundEffect* aSoundEffect)
	{
		if (!m_SoundLibrary->Exists(aSoundEffect))
			return false;

		if (std::shared_ptr<SoundEffect> soundEffect = m_SoundLibrary->Get(aSoundEffect->GetFilepath()))
			m_AudioDevice->Stop(soundEffect);

		return true;
	}
}
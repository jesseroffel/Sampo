#include "sampo_pch.hpp"
#include "sound_library.hpp"

#include "audio_api.hpp"

#ifdef SAMPO_PLATFORM_WINDOWS
#include "platform/windows/audio/sound_effect_win32.hpp"
#endif // SAMPO_PLATFORM_WINDOWS

#include <imgui.h>

namespace Sampo
{
	std::shared_ptr<SoundEffect> SoundLibrary::Create(const std::string& aFilepath, const SoundEffectParams& aSoundEffectParams, bool aPlayOnce)
	{
		if (Exists(aFilepath))
			return m_SoundEffects[aFilepath];

		std::shared_ptr<Sampo::SoundEffect> newSoundEffect = CreateSoundEffect(aFilepath, aSoundEffectParams);
		m_SoundEffects.emplace(aFilepath, newSoundEffect);
		//if (aSoundEffectParams.m_LoadImmediately)
			newSoundEffect->Load();

		if (aPlayOnce)
			newSoundEffect->SetIsOneOff();

		return newSoundEffect;
	}

	std::shared_ptr<Sampo::SoundEffect> SoundLibrary::Get(const std::string& aFilepath)
	{
		return m_SoundEffects[aFilepath];
	}

	bool SoundLibrary::Exists(const SoundEffect* aSoundEffect) const
	{
		for (const auto& [filePath, soundEffect] : m_SoundEffects)
		{
			if (soundEffect->GetSoundEffectID() == aSoundEffect->GetSoundEffectID())
				return true;
		}
		return false;
	}

	bool SoundLibrary::Exists(const std::string& aFilePath) const
	{
		return m_SoundEffects.contains(aFilePath);
	}

#ifdef SAMPO_IMGUI_ENABLED
	void SoundLibrary::ImGuiDebug()
	{
		if (ImGui::TreeNode("Sound Library"))
		{
			ImGui::Text("Total Effects loaded: %u", m_SoundEffects.size());
			for (const auto& [filePath, soundEffect] : m_SoundEffects)
			{
				ImGui::PushID(soundEffect->m_SoundEffectID);
				ImGui::Text("ID: %u", soundEffect->m_SoundEffectID);
				ImGui::Text("Path: %s", soundEffect->GetFilepath().c_str());
				ImGui::Text("Loaded: %s", soundEffect->IsLoaded() ? "True" : "False");
				ImGui::Text("Looping: %s", soundEffect->m_SoundEffectParams.m_Looping ? "True" : "False");
				ImGui::Text("Adjusted volume: %u", soundEffect->m_SoundEffectParams.m_AdjustedVolume);

				if (!soundEffect->IsLoaded() && ImGui::Button("Load"))
					soundEffect.get()->Load();

				if (soundEffect->IsLoaded() && ImGui::Button("Play"))
					Sound::Play(soundEffect.get());

				ImGui::PopID();
			}
			ImGui::TreePop();
		}
	}

	std::shared_ptr<Sampo::SoundEffect> SoundLibrary::CreateSoundEffect(const std::string& aFilepath, const SoundEffectParams& aSoundEffectParams)
	{
		std::shared_ptr<SoundEffect> soundEffect = nullptr;
#ifdef SAMPO_PLATFORM_WINDOWS
		soundEffect = CreateShared<Win32SoundEffect>(aFilepath, aSoundEffectParams);
#endif // SAMPO_PLATFORM_WINDOWS
		
		if (!soundEffect)
			return nullptr;

		soundEffect->m_SoundEffectID = ++m_SoundEffectCount;
		return soundEffect;
	}

#endif // SAMPO_IMGUI_ENABLED
}
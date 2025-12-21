#pragma once
#include "sound_effect.hpp"

namespace Sampo
{
	class SoundLibrary
	{
	public:
		std::shared_ptr<SoundEffect> Create(const std::string& aFilepath, const SoundEffectParams& aSoundEffectParams, bool aPlayOnce);
		std::shared_ptr<SoundEffect> Get(const std::string& aFilepath);
		bool Exists(const std::string& aFilePath) const;
		bool Exists(const SoundEffect* aSoundEffect) const;

		virtual void OnSoundLoaded(void* aCallbackData) { SAMPO_UNUSED(aCallbackData); }

	#ifdef SAMPO_IMGUI_ENABLED
		virtual void ImGuiDebug();
	#endif // SAMPO_IMGUI_ENABLED

	protected:
		std::shared_ptr<SoundEffect> CreateSoundEffect(const std::string& aFilepath, const SoundEffectParams& aSoundEffectParams);
		
		std::unordered_map<std::string, std::shared_ptr<SoundEffect>> m_SoundEffects;
		uint32 m_SoundEffectCount{ 0u };
	};
}
#pragma once

#include "sampo/audio/audio_device.hpp"
#include "sampo/audio/sound_effect.hpp"
#include "sampo/audio/sound_library.hpp"

namespace Sampo
{
	// Application interaction and control interface with sound assets 
	class Sound
	{
	public:
		virtual ~Sound() = default;

		static std::shared_ptr<SoundEffect> Create(const std::string& aFilepath, const SoundEffectParams& aSoundEffectParams = {});

		static bool Play(const SoundEffect* aSoundEffect);
		static bool PlayOnce(const std::string& aFilepath, const SoundEffectParams& aSoundEffectParams = {});

		static void Stop(const std::shared_ptr<SoundEffect>& aSoundEffect);
		static void Stop(const uint32 aSoundEffectID);

		static AudioDevice* GetAudioDevice();
		static SoundLibrary* GetSoundLibrary();
	};

	// Sampo interface core audio vendor handling
	class AudioAPI
	{
		friend Sound;
	public:
		AudioAPI();
		virtual ~AudioAPI() = default;

		static AudioAPI* Create();
		static AudioAPI& GetInstance();

		AudioDevice* GetAudioDevice() { return m_AudioDevice; }
		SoundLibrary* GetSoundLibrary() { return m_SoundLibrary; }

		virtual bool Init();
		virtual void Update();
		virtual void Shutdown();

#ifdef SAMPO_IMGUI_ENABLED
		virtual void ImGuiDebug();
#endif // SAMPO_IMGUI_ENABLED

	protected:
		static AudioAPI* CreateInstance();
		
		virtual AudioConfigParams CreateAudioConfigParams();

		virtual const std::shared_ptr<SoundEffect> CreateSoundEffect(const std::string& aFilepath, const SoundEffectParams& aSoundEffectParams, bool aPlayOnce);

		virtual bool Play(const SoundEffect* aSoundEffect);
		virtual bool PlayOnce(const std::string& aFilepath, const SoundEffectParams& aSoundEffectParams);
		virtual void Stop(const std::shared_ptr<SoundEffect>& aSoundEffect);
		virtual void Stop(const uint32 aSoundEffectID);

		AudioDevice* m_AudioDevice{ nullptr };
		SoundLibrary* m_SoundLibrary{ nullptr };
	private:
		static AudioAPI* s_Instance;
	};

}
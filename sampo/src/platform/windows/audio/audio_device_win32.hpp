#pragma once
#include "sampo/audio/audio_device.hpp"
#include "sound_effect_instance_win32.hpp"

namespace Sampo
{
	class Win32AudioDevice : public AudioDevice
	{
	public:
		Win32AudioDevice() = default;
		virtual ~Win32AudioDevice() = default;

		virtual bool Init(AudioConfigParams& anAudioConfigParams) override;
		virtual void Update() override;
		virtual void Shutdown() override;

		virtual bool Play(std::shared_ptr<SoundEffect> aSoundEffect) override;
		virtual void Stop(std::shared_ptr<Sampo::SoundEffect> aSoundEffect) override;

		virtual void OnSoundAtEnd(void* aSoundEffectData, ma_sound* aMASound);

		ma_engine* GetMAEngine() { return &m_maEngine; }
		//ma_resource_manager* GetMAResourceManager() { return &m_maResourceManager; }

#ifdef SAMPO_IMGUI_ENABLED
		virtual void ImGuiDebug();
#endif // SAMPO_IMGUI_ENABLED

	protected:
		std::shared_ptr<Win32SoundEffectInstance> CreateInstance(std::shared_ptr<SoundEffect> aSoundEffect);
		bool AddActiveInstance(std::shared_ptr<Win32SoundEffectInstance> aNewInstance);

		std::unordered_map<uint32, std::shared_ptr<Win32SoundEffectInstance>> m_ActiveSoundEffectInstances;
		std::vector<std::shared_ptr<Win32SoundEffectInstance>> m_QueuedSoundEffectInstances;
		
		ma_device m_maDevice{};
		ma_engine m_maEngine{};
		ma_resource_manager m_maResourceManager{};
	};
}
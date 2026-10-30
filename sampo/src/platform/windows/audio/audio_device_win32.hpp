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

		virtual bool Init(const AudioConfigParams& anAudioConfigParams) override;
		virtual void Update() override;
		virtual void Shutdown() override;

		virtual bool Play(std::shared_ptr<SoundEffect> aSoundEffect) override;
		virtual void Stop(std::shared_ptr<SoundEffect> aSoundEffect) override;

		void InitDecoderConfig(ma_decoder_config& outMaDecoderConfig);

		virtual void OnSoundAtEnd(void* aSoundEffectData, ma_sound* aMASound);

		ma_engine* GetMAEngine() { return &m_maEngine; }

#ifdef SAMPO_IMGUI_ENABLED
		virtual void ImGuiDebug();
#endif // SAMPO_IMGUI_ENABLED

	protected:
		std::shared_ptr<Win32SoundEffectInstance> CreateInstance(std::shared_ptr<SoundEffect> aSoundEffect);
		bool AddActiveInstance(std::shared_ptr<Win32SoundEffectInstance> aNewInstance);

		std::unordered_map<uint32, std::shared_ptr<Win32SoundEffectInstance>> m_ActiveSoundEffectInstances;
		std::vector<std::shared_ptr<Win32SoundEffectInstance>> m_QueuedSoundEffectInstances;
		std::vector<uint32> m_SoundEffectInstancesAtEnd;
		
		ma_resource_manager m_maResourceManager{};
		ma_decoder_config m_maDecoderConfig{};
		ma_engine m_maEngine{};
		uint32 m_AudioChannels{0};
	};
}
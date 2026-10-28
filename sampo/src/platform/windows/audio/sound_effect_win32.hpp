#pragma once
#include "sampo/audio/sound_effect.hpp"

#include <miniaudio.h>

namespace Sampo
{
	struct MAAsyncLoadFinished
	{
		ma_async_notification_callbacks m_Callbacks;
		void* m_CallbackUserData;
	};

	class Win32SoundEffect : public SoundEffect
	{
	public:
		Win32SoundEffect(const std::string& aFilepath, const SoundEffectParams& aSoundEffectParams);
		virtual ~Win32SoundEffect();

		virtual bool Load() override;
		virtual bool Play() override;
		virtual bool Stop() override;
		virtual bool Unload() override;

		virtual float GetSoundEffectLength() const override;

		bool GetAudioBuffer(ma_audio_buffer_ref& outAudioBufferRef);
		uint32 GetLoadingFlags() const;

	protected:
		std::vector<unsigned char> ReadFileBytes();
		bool LoadDataSource();

		void* m_PCMFrames{nullptr};
		ma_decoder_config m_maDecoderConfig{};
		ma_uint64 m_maFrameCount{0};
		ma_format m_maFormat{ma_format_unknown};
		ma_uint32 m_maChannels{0};

		//ma_data_source* m_maDataSource{nullptr};
		//ma_sound m_maMasterSound;
		//ma_audio_buffer_ref m_maAudioBufferRef;
	};
}
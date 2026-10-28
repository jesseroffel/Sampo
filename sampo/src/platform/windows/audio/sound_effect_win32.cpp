#include "sampo_pch.hpp"
#include "sound_effect_win32.hpp"

#include "sampo/audio/audio_api.hpp"

#include "audio_device_win32.hpp"

#include <filesystem>
#include <fstream>

#include <miniaudio.h>

namespace Sampo
{
	Win32SoundEffect::Win32SoundEffect(const std::string& aFilepath, const SoundEffectParams& aSoundEffectParams)
		: SoundEffect(aFilepath, aSoundEffectParams)
	{
		if (aSoundEffectParams.m_LoadImmediately)
			Load();
	}

	Win32SoundEffect::~Win32SoundEffect()
	{
		Unload();
	}

	bool Win32SoundEffect::Play()
	{
		return Sound::Play(this);
	}

	bool Win32SoundEffect::Stop()
	{
		return Sound::Stop(this);
	}

	bool Win32SoundEffect::Unload()
	{
		//ma_sound_uninit(&m_maMasterSound);
		//ma_audio_buffer_ref_uninit(&m_maAudioBufferRef);
		//ma_free(m_PCMFrames, nullptr);
		return true;
	}

	float Win32SoundEffect::GetSoundEffectLength() const
	{
		//const ma_result readFramesResult = ma_data_source_read_pcm_frames();
		return 0.f;
	}

	bool Win32SoundEffect::GetAudioBuffer(ma_audio_buffer_ref& outAudioBufferRef)
	{
		const ma_result bufferRefInitResult = ma_audio_buffer_ref_init(m_maDecoderConfig.format, m_maDecoderConfig.channels, m_PCMFrames, m_maFrameCount, &outAudioBufferRef);
		if (bufferRefInitResult != MA_SUCCESS)
		{
			SAMPO_CORE_ERROR("Audio API init call 'ma_audio_buffer_ref_init' failed with result code {0}", bufferRefInitResult);
			return false;
		}
		return true;
	}

	bool Win32SoundEffect::Load()
	{
		if (m_IsLoaded)
			return true;

		//LoadDataSource();
		m_IsLoaded = true;
		return true;
	}

	std::vector<unsigned char> Win32SoundEffect::ReadFileBytes()
	{
		std::ifstream file(m_Filepath, std::ios::binary | std::ios::ate);
		if (!file) return {};
		std::streamsize size = file.tellg();
		file.seekg(0, std::ios::beg);
		std::vector<unsigned char> buffer(static_cast<size_t>(size));
		file.read(reinterpret_cast<char*>(buffer.data()), size);
		return buffer;
	}

	bool Win32SoundEffect::LoadDataSource()
	{
		Win32AudioDevice* audioDevice = static_cast<Win32AudioDevice*>(Sound::GetAudioDevice());
		SAMPO_ASSERT_MSG(audioDevice, "No valid Audio Device is active!");

		std::vector<unsigned char> readBytes = ReadFileBytes();

		m_maDecoderConfig = ma_decoder_config_init(ma_format_unknown, 0, 0);

		const ma_result decodeResult = ma_decode_memory(readBytes.data(), readBytes.size(), &m_maDecoderConfig, &m_maFrameCount, &m_PCMFrames);
		if (decodeResult != MA_SUCCESS)
		{
			SAMPO_CORE_ERROR("Audio API init call 'ma_decode_memory' failed with result code {0}", decodeResult);
			return false;
		}

		m_IsLoaded = true;
		return true;
	}

	uint32 Win32SoundEffect::GetLoadingFlags() const
	{
		uint32 m_LoadingFlags{ MA_SOUND_FLAG_NO_SPATIALIZATION | MA_SOUND_FLAG_NO_PITCH };

		//if (m_SoundEffectParams.m_AsyncLoad)
		//	m_LoadingFlags += MA_SOUND_FLAG_ASYNC;

 		if (m_SoundEffectParams.m_Looping)
 			m_LoadingFlags += MA_SOUND_FLAG_LOOPING;

		if (m_SoundEffectParams.m_StreamFile)
			m_LoadingFlags += MA_SOUND_FLAG_STREAM ;

		return m_LoadingFlags;
	}
}
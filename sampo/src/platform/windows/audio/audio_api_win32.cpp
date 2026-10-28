#include "sampo_pch.hpp"
#include "audio_api_win32.hpp"

#include "audio_device_win32.hpp"

namespace Sampo
{
	Win32AudioAPI::Win32AudioAPI()
	{
		m_AudioDevice = new Win32AudioDevice();
	}

	bool Win32AudioAPI::Init()
	{
		AudioConfigParams configParams = CreateAudioConfigParams();
		return m_AudioDevice->Init(configParams);
	}

	bool Win32AudioAPI::Play()
	{
		return false;
	}

	void Win32AudioAPI::Shutdown()
	{
		m_AudioDevice->Shutdown();
	}
}
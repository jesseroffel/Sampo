#pragma once

#include "sampo/audio/audio_api.hpp"

namespace Sampo
{
	class Win32AudioAPI : public AudioAPI
	{
	public:
		Win32AudioAPI();
		virtual ~Win32AudioAPI() = default;

		bool Init() override;
		bool Play();
		void Shutdown() override;
	};
}

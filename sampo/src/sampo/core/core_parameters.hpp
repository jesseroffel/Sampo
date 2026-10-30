#pragma once

namespace Sampo
{
	struct StartParams
	{
		std::string m_ApplicationName;
		std::string m_WindowName;
		std::string m_ExecuteDir;
		std::string m_DataDir;
		bool m_EnableImGui{ false };
		bool m_EnableSound{ true };
		bool m_IsHeadless{ false };

		int m_Argc{ -1 };
		char** m_Argv{ nullptr };
	};

	struct AudioConfigParams
	{
		int m_SampleRate{44100};
		int m_Channels{2};
	};
}
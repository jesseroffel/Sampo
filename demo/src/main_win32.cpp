#include "sampo/core/application.hpp"

int main(int argc, char* argv[])
{
	using namespace Sampo;

	StartParams startParams;
	startParams.m_ApplicationName = "Demo - Sampo Application";
	startParams.m_Argc = argc;
	startParams.m_Argv = argv;
	startParams.m_EnableImGui = true;

	if (!Application::Create(startParams))
	{
		SAMPO_CRITICAL("Unable to start application!");
		return 1;
	}

	Application& application = Application::GetInstance();
	application.Run();
	application.Shutdown();
	return 0;
}
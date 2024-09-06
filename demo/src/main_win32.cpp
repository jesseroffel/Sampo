#include "sampo/core/console_arguments.hpp"
#include "sampo/core/application.hpp"
#include "sampo/io/file_system.hpp"

int main(int argc, char* argv[])
{
	using namespace Sampo;
	ConsoleArguments::Create(argc, argv);

	StartParams startParams;
	startParams.m_IsGame = true;
	startParams.m_ApplicationName = "Demo";

	FileSystem::FileExists("test.txt");

	Log::Init();
	if (!Application::Create(startParams))
	{
		SAMPO_CRITICAL("Unable to start application!");
		return 1;
	}

	return 0;
}
#pragma once
#include "sampo/network/network_core.hpp"
#include "sampo/network/socket_api.hpp"
#include "sampo/core/console_arguments.hpp"

#ifdef SAMPO_PLATFORM_WINDOWS
	extern Sampo::Application* Sampo::CreateApplication();

	int main(int argc, char* argv[])
	{
		Sampo::ConsoleArguments(argc, argv);
		// Init required systems
		Sampo::Log::Init();

		// Application
		auto application = Sampo::CreateApplication();
		application->Run();
		delete application;

		return 0;
	}
#endif // SAMPO_PLATFORM_WINDOWS
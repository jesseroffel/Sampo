#pragma once
#include "sampo/network/network_core.hpp"
#include "sampo/network/socket_api.hpp"
#include "sampo/core/console_arguments.hpp"

void* operator new(std::size_t sz) {
	std::cout << "Allocating: " << sz << '\n';
	return std::malloc(sz);
}

#ifdef SAMPO_PLATFORM_WINDOWS
	extern Sampo::Application* Sampo::CreateApplication();

	int main(int argc, char* argv[])
	{
		Sampo::ConsoleArguments(argc, argv);
		// Init required systems
		Sampo::Log::Init();

		Sampo::Scope<Sampo::SocketAPI> SocketApi = Sampo::SocketAPI::Create();

		SocketApi->Init();

		// Application
		auto application = Sampo::CreateApplication();
		application->Run();
		delete application;

		// Shutdown required systems
		SocketApi->Shutdown();

		return 0;
	}
#endif // SAMPO_PLATFORM_WINDOWS
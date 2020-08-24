#pragma once

#define UNUSED(...) (void)(__VA_ARGS__)

#ifdef SAMPO_PLATFORM_WINDOWS

extern Sampo::Application* Sampo::CreateApplication();

int main(int argc, char** argv)
{
	UNUSED(argc, argv);

	auto application = Sampo::CreateApplication();
	std::cout << "[Sampo initialized]" << '\n';
	application->Run();
	delete application;

	return 0;
}

#endif
#pragma once

#ifdef SAMPO_PLATFORM_WINDOWS

extern Sampo::Application* Sampo::CreateApplication();

int main(int argc, char** argv)
{
	UNUSED(argc, argv);

	auto application = Sampo::CreateApplication();
	application->Init();
	application->Run();
	delete application;

	return 0;
}

#endif
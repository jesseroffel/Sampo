#include "core/engine.h"

namespace Rakas
{
	Engine* s_Engine = nullptr;

	Engine* Engine::Rakas_Init(I8 flags)
	{
		flags++;
		if (s_Engine == nullptr)
		{
			s_Engine = new Engine();
		}

		return s_Engine;
	}

	void Engine::Rakas_Quit()
	{
		if (s_Engine != nullptr)
		{
			delete s_Engine;
		}
	}

	Engine* Engine::GetInstance()
	{
		return s_Engine;
	}

	Engine::Engine()
	{

	}
}

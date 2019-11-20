#pragma once
#include <memory>
#include "core/core_defines.h"

namespace Rakas
{
	namespace IO { class FileSystem; }

	class Window;
	class Engine final
	{
	public:
		static Engine* Rakas_Init(I8 flags);
		static void Rakas_Quit();

		static Engine* GetInstance();

		virtual ~Engine() = default;

		Engine(const Engine&) = delete;
		Engine& operator=(const Engine&) = delete;

		Engine(Engine&&) = delete;
		Engine& operator=(Engine&&) = delete;


	private:
		Engine();

		//Systems
 		//std::unique_ptr<Window> m_GameWindow							= nullptr;
 		//std::unique_ptr<Graphics::GraphicsContext> m_GraphicsContext	= nullptr;
		//std::unique_ptr<IO::FileSystem> m_FileSystem					= nullptr;

		bool	m_Running	= false;
	};
}
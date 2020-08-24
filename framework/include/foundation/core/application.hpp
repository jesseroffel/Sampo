#pragma once
// Application Class, using the main entry point to start common systems, to be defined in the client application // 
#include "core_definitions.hpp"

namespace Sampo {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void Close();

		inline static Application& Get() { return *s_Instance; }
	private:
		bool m_Running = true;
	private:
		static Application* s_Instance;
	};


	// To be defined in the client application using Sampo //
	Application* CreateApplication();
}
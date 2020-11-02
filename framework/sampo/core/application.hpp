#pragma once
// Application Class, using the main entry point to start common systems, to be defined in the client application // 
#include "core_definitions.hpp"
#include "layer.hpp"

namespace Sampo {
	class Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void Init() {}
		void Run();
		void Close();

		inline static Application& Get() { return *s_Instance; }

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
	private:
		void InitSampo();					// Init Systems required
	private:
		bool m_Running = true;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
	};


	// To be defined in the client application using Sampo //
	Application* CreateApplication();
}
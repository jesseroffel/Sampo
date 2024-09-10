#pragma once
#include "layer.hpp"
#include "platform.hpp"

// Application Class, using the main entry point to start common systems, to be defined in the client application // 
namespace Sampo 
{
	struct StartParams
	{
		std::string m_ApplicationName;
		std::string m_WindowName;
		std::string m_ExecuteDir;
		std::string m_DataDir;

		int m_Argc{ -1 };
		char** m_Argv{ nullptr };
	};

	class Application
	{
	public:
		static Application* Create(StartParams& aStartParams);
		static Application& GetInstance();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);

		void Run();
		void Shutdown();

	protected:
		virtual ~Application();

		static Application* CreateApplication();

		virtual bool Init(StartParams& aStartParams);

		bool m_Running = true;
		LayerStack m_LayerStack;

		Platform* m_Platform;

	private:
		static Application* s_Instance;
	};
}
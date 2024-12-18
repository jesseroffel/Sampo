#pragma once
#include "layer.hpp"
#include "platform.hpp"

// Application Class, using the main entry point to start common systems, to be defined in the client application // 
namespace Sampo 
{
	class Event;
	class ImGuiLayer;
	class WindowCloseEvent;

	struct StartParams
	{
		std::string m_ApplicationName;
		std::string m_WindowName;
		std::string m_ExecuteDir;
		std::string m_DataDir;
		bool m_EnableImGui{ false };

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

		void OnEvent(Event& anEvent);

		void Run();
		void Shutdown();

		const Platform* GetPlatform() const { return m_Platform; }

	protected:
		virtual ~Application() = default;

		static Application* CreateApplication();

		virtual bool Init(StartParams& aStartParams);

		void OnWindowClose();

		LayerStack m_LayerStack;

		Platform* m_Platform{ nullptr };
		ImGuiLayer* m_ImGuiLayer{ nullptr };

		bool m_Running{ true };
		float m_Time{ 0.0f };

	private:
		static Application* s_Instance;
	};
}
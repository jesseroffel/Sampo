#pragma once
#include "layer.hpp"
#include "platform.hpp"
#include "core_parameters.hpp"

// Application Class, using the main entry point to start common systems, to be defined in the client application // 
namespace Sampo 
{
	class ImGuiLayer;

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
		virtual ~Application();

		static Application* CreateApplication();

		virtual bool Init(StartParams& aStartParams);

		void OnWindowClose();
		void OnWindowMinimize(Event& aWindowMinimizeEvent);

		LayerStack m_LayerStack;

		Platform* m_Platform{ nullptr };
#ifdef SAMPO_IMGUI_ENABLED
		ImGuiLayer* m_ImGuiLayer{ nullptr };
#endif // SAMPO_IMGUI_ENABLED

		float m_LastFrameTime{ 0.0f };

		bool m_Running{ true };
		bool m_Minimized{ false };
	private:
		static Application* s_Instance;
	};
}
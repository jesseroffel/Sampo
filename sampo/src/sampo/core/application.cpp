#include "sampo_pch.hpp"
#include "application.hpp"

#include "console_arguments.hpp"
#include "platform.hpp"
#include "timestep.hpp"

#include "sampo/debugging/imgui_layer.hpp"
#include "sampo/events/application_event.hpp"
#include "sampo/graphics/window.hpp"
#include "sampo/graphics/renderer.hpp"

namespace Sampo
{
	Application* Application::s_Instance = nullptr;

	Application* Application::Create(StartParams& aStartParams)
	{
		SAMPO_ASSERT_MSG(!s_Instance, "Sampo already initialized!");

		s_Instance = CreateApplication();

		ConsoleArguments::Create(aStartParams.m_Argc, aStartParams.m_Argv);

		Log::Create();

		s_Instance->Init(aStartParams);
		return s_Instance;
	}

	Application& Application::GetInstance()
	{
		SAMPO_ASSERT_MSG(s_Instance, "Application instance has not been created!");
		return *s_Instance;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PopLayer(Layer* layer)
	{
		m_LayerStack.PopLayer(layer);
		layer->OnDetach();
	}

	void Application::OnEvent(Event& anEvent)
	{
		if (anEvent.GetEventType() == EventType::WindowClose)
			OnWindowClose();
		else if (anEvent.GetEventType() == EventType::WindowMinimize)
			OnWindowMinimize(anEvent);

		for (auto iter = m_LayerStack.end(); iter != m_LayerStack.begin(); )
		{
			(*--iter)->OnEvent(anEvent);
			if (anEvent.m_Processed)
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			const Platform* platform = GetPlatform();
			const float platformTime = platform->GetTime();
			Timestep deltaTime = platformTime - m_LastFrameTime;
			m_LastFrameTime = platformTime;

			Window* window = platform->GetWindow();
			window->OnStartFrame();

			if (m_Platform)
				m_Platform->Update();

			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(deltaTime);
			}

			m_ImGuiLayer->Begin();

			m_Platform->ImGuiDebug(); // TODO - change to debugger container for ImGui rendering

			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();

			m_ImGuiLayer->End();

			if (!m_Minimized)
			{
				window->Update();
				window->OnEndFrame();
			}
		}
	}

	void Application::Shutdown()
	{
		SAMPO_ASSERT_MSG(s_Instance, "Application instance already shut down!");
 
		m_Platform->Shutdown();
		delete m_Platform;
		m_Platform = nullptr;

		delete s_Instance;
		s_Instance = nullptr;
	}

	Application* Application::CreateApplication()
	{
#ifdef SAMPO_PLATFORM_WINDOWS
		return new Application();
#endif // SAMPO_PLATFORM_WINDOWS
	}

	bool Application::Init(StartParams& aStartParams)
	{
		m_Platform = new Platform();
		m_Platform->Init(aStartParams.m_ApplicationName);

		Renderer::Init();

		if (aStartParams.m_EnableImGui)
		{
			m_ImGuiLayer = new ImGuiLayer();
			PushLayer(m_ImGuiLayer);
		}

		SAMPO_CORE_TRACE("[Sampo initialized]");
		return true;
	}

	void Application::OnWindowClose()
	{
		m_Running = false;
	}

	void Application::OnWindowMinimize(Event& aWindowMinimizeEvent)
	{
		WindowsMinimizeEvent& minimizeEvent = static_cast<WindowsMinimizeEvent&>(aWindowMinimizeEvent);
		m_Minimized = minimizeEvent.GetIsMinimizing();
	}
}
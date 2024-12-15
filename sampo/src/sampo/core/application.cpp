#include "sampo_pch.hpp"
#include "application.hpp"

#include "console_arguments.hpp"
#include "sampo/events/application_event.hpp"

#include "sampo/core/platform.hpp"
#include "sampo/graphics/window.hpp"

namespace Sampo {
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

	Application::~Application()
	{
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
		m_LayerStack.PushLayer(layer);
		layer->OnDetach();
	}

	void Application::OnEvent(Event& anEvent)
	{
		if (anEvent.GetEventType() == EventType::WindowClose)
			OnWindowClose();
	}

	void Application::Run()
	{
		while (m_Running)
		{
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(0);

			if (m_Platform)
				m_Platform->Update();
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

		Window* window = m_Platform->GetWindow();
		window->SetWindowEventCallback(BIND_EVENT_FN(Application::OnEvent, this));

		SAMPO_CORE_TRACE("[Sampo initialized]");
		return true;
	}

	void Application::OnWindowClose()
	{
		m_Running = false;
	}
}
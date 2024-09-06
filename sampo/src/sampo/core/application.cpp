#include "sampo_pch.hpp"
#include "application.hpp"

#ifdef SAMPO_PLATFORM_WINDOWS
#include "platform/windows/game_win32.hpp"
#endif // SAMPO_PLATFORM_WINDOWS

namespace Sampo {
	Application* Application::s_Instance = nullptr;

    Application* Application::Create(StartParams& startParams)
	{
        if (s_Instance)
        {
            SAMPO_CORE_CRITICAL("Sampo already initialized!");
            return nullptr;
        }

        if (startParams.m_IsGame)
        {
		    s_Instance = CreateApplication();
            s_Instance->Init(startParams);
        }

        if (startParams.m_EnableNetworking)
        {
            //Sampo::Scope<Sampo::SocketAPI> SocketApi = Sampo::SocketAPI::Create();
            //SocketApi->Init();
        }

        SAMPO_CORE_TRACE("[Sampo initialized]");
        return s_Instance;
	}

    Application* Application::CreateApplication()
    {
#ifdef SAMPO_PLATFORM_WINDOWS
        return new Win32Game();
#endif // SAMPO_PLATFORM_WINDOWS
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

    void Application::Run()
	{
        while (m_Running)
        {
            for (Layer* layer : m_LayerStack)
                layer->OnUpdate(0);
        }
	}
}
#include "sampo_pch.hpp"
#include "application.hpp"

#include "entry_point.hpp"

namespace Sampo {
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
        if (s_Instance)
        {
            SAMPO_CORE_CRITICAL("Sampo already initialized!");
            return;
        }

		s_Instance = this;

        SAMPO_CORE_TRACE("[Sampo initialized]");
	}

    void Application::Close()
    {
		m_Running = false;
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
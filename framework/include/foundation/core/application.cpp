#include "sampo_pch.hpp"
#include "application.hpp"
#include "entry_point.hpp"

namespace Sampo {
	
    void Application::InitSampo()
    {
        std::cout << "[Sampo initialized]" << '\n';
    }

    // Client //
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		s_Instance = this;
        InitSampo();
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
		char test = '0';
		std::cin >> test;
	}

    Application::~Application()
    {
    }

}
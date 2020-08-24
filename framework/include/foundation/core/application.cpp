#include "sampo_pch.hpp"
#include "application.hpp"
#include "entry_point.hpp"

namespace Sampo {
	
	// Client //
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		s_Instance = this;
	}


    void Application::Close()
    {
		m_Running = false;
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
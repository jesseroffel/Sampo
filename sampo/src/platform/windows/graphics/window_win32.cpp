#include "sampo_pch.hpp"
#include "window_win32.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Sampo
{
	Win32Window::~Win32Window()
	{
		Shutdown();
	}

	void Win32Window::Init(const WindowParams& aWindowProperties)
	{
		m_Params = aWindowProperties;

		SAMPO_CORE_INFO("Creating window [{0}] ({1}, {2})", m_Params.m_WindowName, m_Params.m_Width, m_Params.m_Height);

		if (!m_GLFWInitialized)
		{
			SAMPO_ASSERT_MSG(glfwInit(), "Failed to init GLFW!");
			m_GLFWInitialized = true;
		}

		m_GLFWWindow = glfwCreateWindow((int)m_Params.m_Width, m_Params.m_Height, m_Params.m_WindowName.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_GLFWWindow);
		SAMPO_ASSERT_MSG(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize Glad!");

		glfwSetWindowUserPointer(m_GLFWWindow, &m_Params);
		SetVSync(true);
	}

	void Win32Window::Update()
	{
		glClearColor(0, 0, 0.5, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();
		glfwSwapBuffers(m_GLFWWindow);
	}

	void Win32Window::Shutdown()
	{
		SAMPO_ASSERT_MSG(m_GLFWWindow, "Window does not exists!");
		glfwDestroyWindow(m_GLFWWindow);
		m_GLFWWindow = nullptr;
	}

	void Win32Window::SetVSync(bool anEnable)
	{
		glfwSwapInterval(anEnable ? 1 : 0);
	}
}
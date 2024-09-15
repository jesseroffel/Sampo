#include "sampo_pch.hpp"
#include "window_win32.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "sampo/events/application_event.hpp"
#include "sampo/events/key_event.hpp"
#include "sampo/events/mouse_event.hpp"

namespace Sampo
{
	Win32Window::~Win32Window()
	{
		SAMPO_ASSERT_MSG(!m_GLFWWindow, "Window is still active!");
	}

	bool Win32Window::Init(const WindowParams& aWindowProperties)
	{
		m_Params = aWindowProperties;

		SAMPO_CORE_INFO("Creating window [{0}] ({1}, {2})", m_Params.m_WindowName, m_Params.m_Width, m_Params.m_Height);

		if (!m_GLFWInitialized)
		{
			SAMPO_ASSERT_MSG(glfwInit(), "Failed to init GLFW!");
			m_GLFWInitialized = true;
			glfwSetErrorCallback([](int anErrorCode, const char* aDescription)
			{
				SAMPO_CORE_ERROR("GLFW Error ({0}): {1}", anErrorCode, aDescription);
			});
		}

		m_GLFWWindow = glfwCreateWindow((int)m_Params.m_Width, m_Params.m_Height, m_Params.m_WindowName.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_GLFWWindow);
		SAMPO_ASSERT_MSG(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize Glad!");

		glfwSetWindowUserPointer(m_GLFWWindow, &m_Params);
		SetVSync(true);

		LogRendererInfo();
		SetGLFWCallbacks();
		return true;
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

	void Win32Window::LogRendererInfo()
	{
		int glfwMajor = glfwGetWindowAttrib(m_GLFWWindow, GLFW_CONTEXT_VERSION_MAJOR);
		int glfwMinor = glfwGetWindowAttrib(m_GLFWWindow, GLFW_CONTEXT_VERSION_MINOR);
		int glfwRevision = glfwGetWindowAttrib(m_GLFWWindow, GLFW_CONTEXT_REVISION);

		SAMPO_CORE_INFO("Glfw: {0}.{1}.{2}", glfwMajor, glfwMinor, glfwRevision);

		const auto glVendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
		const auto glRenderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
		const auto glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
		const auto glShaderVersion = reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));

		SAMPO_CORE_INFO("OpenGL Vendor {0}", glVendor);
		SAMPO_CORE_INFO("OpenGL Renderer {0}", glRenderer);
		SAMPO_CORE_INFO("OpenGL Version {0}", glVersion);
		SAMPO_CORE_INFO("OpenGL Shader Version {0}", glShaderVersion);
	}

	void Win32Window::SetGLFWCallbacks()
	{
		glfwSetWindowSizeCallback(m_GLFWWindow, [](GLFWwindow* aWindow, int aWidth, int aHeight)
		{
			WindowParams& params = *static_cast<WindowParams*>(glfwGetWindowUserPointer(aWindow));
			params.m_Width = aWidth;
			params.m_Height = aHeight;

			WindowsResizeEvent windowEvent(aWidth, aHeight);
			params.m_EventCallback(windowEvent);
		});

		glfwSetWindowCloseCallback(m_GLFWWindow, [](GLFWwindow* aWindow)
		{
			WindowParams& params = *static_cast<WindowParams*>(glfwGetWindowUserPointer(aWindow));

			WindowCloseEvent closeEvent;
			params.m_EventCallback(closeEvent);
		});

		glfwSetKeyCallback(m_GLFWWindow, [](GLFWwindow* aWindow, int aKey, int aScancode, int anAction, int aMods)
		{
			SAMPO_UNUSED(aScancode);
			SAMPO_UNUSED(aMods);

			WindowParams& params = *static_cast<WindowParams*>(glfwGetWindowUserPointer(aWindow));

			switch (anAction)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent keyPressEvent(aKey, 0);
					params.m_EventCallback(keyPressEvent);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent keyReleasedEvent(aKey);
					params.m_EventCallback(keyReleasedEvent);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent keyRepeatEvent(aKey, 1);
					params.m_EventCallback(keyRepeatEvent);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(m_GLFWWindow, [](GLFWwindow* aWindow, int aButton, int anAction, int aMods)
		{
			SAMPO_UNUSED(aMods);

			WindowParams& params = *static_cast<WindowParams*>(glfwGetWindowUserPointer(aWindow));

			switch (anAction)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent mousePressedEvent(aButton);
					params.m_EventCallback(mousePressedEvent);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent mouseReleasedEvent(aButton);
					params.m_EventCallback(mouseReleasedEvent);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_GLFWWindow, [](GLFWwindow* aWindow, double xOffset, double yOffset)
		{
			WindowParams& params = *static_cast<WindowParams*>(glfwGetWindowUserPointer(aWindow));

			MouseScrolledEvent mouseScrollEvent(static_cast<float>(xOffset), static_cast<float>(yOffset));
			params.m_EventCallback(mouseScrollEvent);
		});

		glfwSetCursorPosCallback(m_GLFWWindow, [](GLFWwindow* aWindow, double xPosition, double yPosition)
		{
			WindowParams& params = *static_cast<WindowParams*>(glfwGetWindowUserPointer(aWindow));

			MouseMovedEvent mouseMovedEvent(static_cast<float>(xPosition), static_cast<float>(yPosition));
			params.m_EventCallback(mouseMovedEvent);
		});
	}
}
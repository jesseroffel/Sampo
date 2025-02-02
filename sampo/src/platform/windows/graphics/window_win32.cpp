#include "sampo_pch.hpp"
#include "window_win32.hpp"

#include "sampo/core/application.hpp"

#include "sampo/events/application_event.hpp"
#include "sampo/events/key_event.hpp"
#include "sampo/events/mouse_event.hpp"
#include "sampo/events/gamepad_event.hpp"

#include "platform/opengl/opengl_context.hpp"

#include <GLFW/glfw3.h>

namespace Sampo
{
	Win32Window::~Win32Window()
	{
		SAMPO_ASSERT_MSG(!m_GLFWWindow, "Window is still active!");
	}

	bool Win32Window::Init(const WindowParams& aWindowProperties)
	{
		m_Params = aWindowProperties;
		const glm::vec2& aWindowSize = m_Params.m_WindowSize;
		SAMPO_CORE_INFO("Creating window [{0}] ({1}, {2})", m_Params.m_WindowName, aWindowSize.x, aWindowSize.y);

		if (!m_GLFWInitialized)
		{
			SAMPO_ASSERT_MSG(glfwInit(), "Failed to init GLFW!");
			m_GLFWInitialized = true;
			glfwSetErrorCallback([](int anErrorCode, const char* aDescription)
			{
				SAMPO_CORE_ERROR("GLFW Error ({0}): {1}", anErrorCode, aDescription);
			});
		}

		m_GLFWWindow = glfwCreateWindow(static_cast<int>(aWindowSize.x), static_cast<int>(aWindowSize.y), m_Params.m_WindowName.c_str(), nullptr, nullptr);
		
		m_GraphicsContext = new OpenGLContext(this, m_GLFWWindow);
		m_GraphicsContext->Init();

		glfwSetWindowUserPointer(m_GLFWWindow, &m_Params);
		SetVSync(true);

		m_GraphicsContext->LogRendererInfo();
		SetGLFWCallbacks();

		m_GraphicsContext->PostInit();
		return true;
	}

	void Win32Window::OnStartFrame()
	{
		m_GraphicsContext->OnStartFrame();
	}

	void Win32Window::Update()
	{
		m_GraphicsContext->Draw();
	}

	void Win32Window::OnEndFrame()
	{
		m_GraphicsContext->SwapBuffers();
	}

	void Win32Window::Shutdown()
	{
		SAMPO_ASSERT_MSG(m_GLFWWindow, "Window does not exists!");
		glfwDestroyWindow(m_GLFWWindow);
		m_GLFWWindow = nullptr;
	}

	float Win32Window::GetTime() const
	{
		return static_cast<float>(glfwGetTime());
	}

	void Win32Window::SetVSync(bool anEnable)
	{
		glfwSwapInterval(anEnable ? 1 : 0);
	}

	void Win32Window::SetGLFWCallbacks()
	{
		glfwSetWindowSizeCallback(m_GLFWWindow, [](GLFWwindow* aWindow, int aWidth, int aHeight)
		{
			WindowParams& params = *static_cast<WindowParams*>(glfwGetWindowUserPointer(aWindow));
			params.m_WindowSize.x = static_cast<glm::vec2::value_type>(aWidth);
			params.m_WindowSize.y = static_cast<glm::vec2::value_type>(aHeight);

			WindowsResizeEvent windowEvent(aWidth, aHeight);
			params.m_WindowEventCallback(windowEvent);
		});

		glfwSetWindowCloseCallback(m_GLFWWindow, [](GLFWwindow* aWindow)
		{
			WindowParams& params = *static_cast<WindowParams*>(glfwGetWindowUserPointer(aWindow));

			WindowCloseEvent closeEvent;
			params.m_WindowEventCallback(closeEvent);
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
					params.m_KeyboardEventCallback(keyPressEvent);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent keyReleasedEvent(aKey);
					params.m_KeyboardEventCallback(keyReleasedEvent);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent keyRepeatEvent(aKey, 1);
					params.m_KeyboardEventCallback(keyRepeatEvent);
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
					params.m_MouseEventCallback(mousePressedEvent);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent mouseReleasedEvent(aButton);
					params.m_MouseEventCallback(mouseReleasedEvent);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_GLFWWindow, [](GLFWwindow* aWindow, double anOffsetX, double anOffsetY)
		{
			WindowParams& params = *static_cast<WindowParams*>(glfwGetWindowUserPointer(aWindow));

			MouseScrolledEvent mouseScrollEvent({ anOffsetX, anOffsetY });
			params.m_MouseEventCallback(mouseScrollEvent);
		});

		glfwSetCursorPosCallback(m_GLFWWindow, [](GLFWwindow* aWindow, double aPositionX, double aPositionY)
		{
			WindowParams& params = *static_cast<WindowParams*>(glfwGetWindowUserPointer(aWindow));

			MouseMovedEvent mouseMovedEvent({ aPositionX, aPositionY });
			params.m_MouseEventCallback(mouseMovedEvent);
		});

		glfwSetJoystickCallback([](int aJoystickId, int anEventId)
		{
			GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetInstance().GetPlatform()->GetWindow()->GetNativeWindow());
			if (!window)
				return;

			WindowParams& params = *static_cast<WindowParams*>(glfwGetWindowUserPointer(window));
			switch (anEventId)
			{
			case GLFW_CONNECTED:
			{
				GamepadConnectedEvent joystickConnectedEvent(aJoystickId);
				params.m_JoystickEventCallback(joystickConnectedEvent);
				break;
			}
			case GLFW_DISCONNECTED:
			{
				GamepadDisconnectedEvent joystickDisconnectedEvent(aJoystickId);
				params.m_JoystickEventCallback(joystickDisconnectedEvent);
				break;
			}
			}
		});
	}
}
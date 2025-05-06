#include "sampo_pch.hpp"
#include "opengl_context.hpp"

#include "sampo/graphics/render_command.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Sampo
{
	OpenGLContext::OpenGLContext(Window* aWindow, GLFWwindow* aWindowHandle)
		: m_Window(aWindow)
		, m_WindowHandle(aWindowHandle)
	{
		SAMPO_ASSERT_MSG(m_Window, "Window must be provided to set up OpenGL Context!");
		SAMPO_ASSERT_MSG(m_WindowHandle, "Window Handle must be set in order to setup OpenGL Context!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		SAMPO_ASSERT_MSG(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize Glad!");

		RenderCommand::SetClearColor({ 0.075f, 0.15f, 0.25f, 1 });
	}

	void OpenGLContext::OnStartFrame()
	{
		const glm::vec2& windowSize = m_Window->GetWindowSize();
		glViewport(0, 0, static_cast<int>(windowSize.x), static_cast<int>(windowSize.y));
		glfwPollEvents();
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

	void OpenGLContext::LogRendererInfo()
	{
		int glfwMajor = glfwGetWindowAttrib(m_WindowHandle, GLFW_CONTEXT_VERSION_MAJOR);
		int glfwMinor = glfwGetWindowAttrib(m_WindowHandle, GLFW_CONTEXT_VERSION_MINOR);
		int glfwRevision = glfwGetWindowAttrib(m_WindowHandle, GLFW_CONTEXT_REVISION);

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
}
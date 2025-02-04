#include "sampo_pch.hpp"
#include "opengl_context.hpp"

#include "sampo/graphics/buffer.hpp"
#include "sampo/graphics/shader.hpp"

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

		glClearColor(0.075f, 0.15f, 0.25f, 1);
	}

	void OpenGLContext::PostInit()
	{
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		uint32 indices[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32)));

		std::string vertexSource = R"(
			#version 330 core
			
			layout(location = 0) in vec3 aPosition;

			out vec3 vPosition;

			void main()
			{
				vPosition = aPosition;
				gl_Position = vec4(aPosition, 1.0);
			}
		)";

		std::string fragmentSource = R"(
			#version 330 core
			
			layout(location = 0) out vec4 colorOut;

			in vec3 vPosition;

			void main()
			{
				colorOut = vec4((vPosition * 0.5) + 0.5, 1.0);
			}
		)";

		m_Shader.reset(new Shader(vertexSource, fragmentSource));
	}

	void OpenGLContext::OnStartFrame()
	{
		const glm::vec2& windowSize = m_Window->GetWindowSize();
		glViewport(0, 0, static_cast<int>(windowSize.x), static_cast<int>(windowSize.y));
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_WindowHandle);
	}

	void OpenGLContext::Draw()
	{
		m_Shader->Bind();

		glBindVertexArray(m_VertexArray);
		glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
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
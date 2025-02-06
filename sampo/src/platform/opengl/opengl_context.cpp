#include "sampo_pch.hpp"
#include "opengl_context.hpp"

#include "sampo/graphics/buffer.hpp"
#include "sampo/graphics/shader.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Sampo
{
	static GLenum ShaderDataTypeToOpenGLType(ShaderDataType aDataType)
	{
		switch (aDataType)
		{
		case Sampo::ShaderDataType::None:
		case Sampo::ShaderDataType::Bool: return GL_BOOL;
		case Sampo::ShaderDataType::Int: return GL_INT;
		case Sampo::ShaderDataType::Int2: return GL_INT;
		case Sampo::ShaderDataType::Int3: return GL_INT;
		case Sampo::ShaderDataType::Int4: return GL_INT;
		case Sampo::ShaderDataType::Float: return GL_FLOAT;
		case Sampo::ShaderDataType::Float2: return GL_FLOAT;
		case Sampo::ShaderDataType::Float3: return GL_FLOAT;
		case Sampo::ShaderDataType::Float4: return GL_FLOAT;
		case Sampo::ShaderDataType::Mat3: return GL_FLOAT;
		case Sampo::ShaderDataType::Mat4: return GL_FLOAT;
		}

		SAMPO_ASSERT_MSG(false, "Cannot convert Shader Data Type to OpenGL Type as the data type is invalid!");
		return 0;
	}

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

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.75f, 0.25f, 0.75f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.25f, 0.3f, 0.75f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.75f, 0.75f, 0.25f, 1.0f,
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout = {
			{ ShaderDataType::Float3, "aPosition"},
			{ ShaderDataType::Float4, "aColor" }
		};
		m_VertexBuffer->SetLayout(layout);

		uint32 index = 0;
		const BufferLayout& vertexLayout = m_VertexBuffer->GetLayout();
		for (const BufferElement& bufferElement : vertexLayout)
		{
			glEnableVertexAttribArray(index);
			const uint32 componentCount = bufferElement.GetComponentCount();
			const GLenum dataType = ShaderDataTypeToOpenGLType(bufferElement.m_Type);
			const GLboolean normalized = bufferElement.m_Normalized ? GL_TRUE : GL_FALSE;
			const uint32 stride = vertexLayout.GetStride();
			glVertexAttribPointer(index, componentCount, dataType, normalized, stride, (const void*)bufferElement.m_Offset);
			index++;
		}


		uint32 indices[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32)));

		std::string vertexSource = R"(
			#version 330 core
			
			layout(location = 0) in vec3 aPosition;
			layout(location = 1) in vec4 aColor;

			out vec3 vPosition;
			out vec4 vColor;

			void main()
			{
				vPosition = aPosition;
				vColor = aColor;
				gl_Position = vec4(aPosition, 1.0);
			}
		)";

		std::string fragmentSource = R"(
			#version 330 core
			
			layout(location = 0) out vec4 colorOut;

			in vec3 vPosition;
			in vec4 vColor;

			void main()
			{
				colorOut = vec4((vPosition * 0.5) + 0.5, 1.0);
				colorOut = vColor;
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
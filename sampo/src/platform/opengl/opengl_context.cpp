#include "sampo_pch.hpp"
#include "opengl_context.hpp"

#include "sampo/graphics/buffer.hpp"
#include "sampo/graphics/shader.hpp"
#include "sampo/graphics/vertex_array.hpp"
#include "sampo/graphics/renderer.hpp"
#include "sampo/graphics/render_command.hpp"

#include "platform/opengl/opengl_renderer_api.hpp"

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

	void OpenGLContext::PostInit()
	{
		m_VertexArray.reset(VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.75f, 0.25f, 0.75f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.25f, 0.3f, 0.75f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.75f, 0.75f, 0.25f, 1.0f,
		};

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout = {
			{ ShaderDataType::Float3, "aPosition"},
			{ ShaderDataType::Float4, "aColor" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32 indices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

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

		m_SquareVA.reset(VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			 -0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({ { ShaderDataType::Float3, "aPosition" } });
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32 squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSquareSource = R"(
			#version 330 core
			
			layout(location = 0) in vec3 aPosition;

			out vec3 vPosition;

			void main()
			{
				vPosition = aPosition;
				gl_Position = vec4(aPosition, 1.0);
			}
		)";

		std::string fragmentSquareSource = R"(
			#version 330 core
			
			layout(location = 0) out vec4 colorOut;

			in vec3 vPosition;

			void main()
			{
				colorOut = vec4(0.25, 0.35, 0.75, 1.0);
			}
		)";

		m_SquareShader.reset(new Shader(vertexSquareSource, fragmentSquareSource));

	}

	void OpenGLContext::OnStartFrame()
	{
		const glm::vec2& windowSize = m_Window->GetWindowSize();
		glViewport(0, 0, static_cast<int>(windowSize.x), static_cast<int>(windowSize.y));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_WindowHandle);
	}

	void OpenGLContext::Draw()
	{
		RenderCommand::Clear();

		Renderer::BeginScene();

		m_SquareShader->Bind();
		Renderer::Submit(m_SquareVA);

		m_Shader->Bind();
		Renderer::Submit(m_VertexArray);

		Renderer::EndScene();
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
#include "sampo_pch.hpp"
#include "renderer2D.hpp"

#include "vertex_array.hpp"
#include "shader.hpp"
#include "render_command.hpp"
#include "buffer.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace Sampo
{
	struct Renderer2DStorage
	{
		std::shared_ptr<VertexArray> m_QuadVertexArray;
		std::shared_ptr<Shader> m_FlatcolorShader;
	};

	static Renderer2DStorage* s_Renderer2DStorage;

	void Renderer2D::Init()
	{
		s_Renderer2DStorage = new Renderer2DStorage();
		s_Renderer2DStorage->m_QuadVertexArray = VertexArray::Create();

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			 -0.5f, 0.5f, 0.0f
		};

		std::shared_ptr<VertexBuffer> squareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({ { ShaderDataType::Float3, "aPosition" } });
		s_Renderer2DStorage->m_QuadVertexArray->AddVertexBuffer(squareVB);

		uint32 squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> squareIB = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32));
		s_Renderer2DStorage->m_QuadVertexArray->SetIndexBuffer(squareIB);

		s_Renderer2DStorage->m_FlatcolorShader = Shader::Create("../../../../../demo/data/assets/shaders/flatcolor.glsl");
	}

	void Renderer2D::Shutdown()
	{
		delete s_Renderer2DStorage;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& aCamera)
	{
		s_Renderer2DStorage->m_FlatcolorShader->Bind();
		s_Renderer2DStorage->m_FlatcolorShader->SetMatrix4("uViewProjection", aCamera.GetViewProjectionMatrix());
		s_Renderer2DStorage->m_FlatcolorShader->SetMatrix4("uTransform", glm::mat4(1.0f));
	}

	void Renderer2D::DrawQuad(const glm::vec2& aPosition, const glm::vec2& aSize, const glm::vec4& aColor)
	{
		DrawQuad({ aPosition.x, aPosition.y, 0.0f }, aSize, aColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& aPosition, const glm::vec2& aSize, const glm::vec4& aColor)
	{
		s_Renderer2DStorage->m_FlatcolorShader->Bind();
		s_Renderer2DStorage->m_FlatcolorShader->SetFloat4("uColor", aColor);

		s_Renderer2DStorage->m_FlatcolorShader->Bind();
		s_Renderer2DStorage->m_FlatcolorShader->SetFloat4("uViewProjection", aColor);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), aPosition) * glm::scale(glm::mat4(1.0f), { aSize.x, aSize.y, 1.0f });
		s_Renderer2DStorage->m_FlatcolorShader->SetMatrix4("uTransform", transform);

		s_Renderer2DStorage->m_QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Renderer2DStorage->m_QuadVertexArray);
	}
}
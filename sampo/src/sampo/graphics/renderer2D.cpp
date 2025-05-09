#include "sampo_pch.hpp"
#include "renderer2D.hpp"

#include "vertex_array.hpp"
#include "shader.hpp"
#include "render_command.hpp"
#include "buffer.hpp"
#include "texture.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace Sampo
{
	struct Renderer2DStorage
	{
		std::shared_ptr<VertexArray> m_QuadVertexArray;
		std::shared_ptr<Shader> m_TextureShader;
		std::shared_ptr<Texture2D> m_WhiteTexture;
	};

	static Renderer2DStorage* s_Renderer2DStorage;

	void Renderer2D::Init()
	{
		s_Renderer2DStorage = new Renderer2DStorage();
		s_Renderer2DStorage->m_QuadVertexArray = VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			 -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
		};

		std::shared_ptr<VertexBuffer> squareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({ 
			{ ShaderDataType::Float3, "aPosition" },
			{ ShaderDataType::Float2, "aTextureCoord" }
		});
		s_Renderer2DStorage->m_QuadVertexArray->AddVertexBuffer(squareVB);

		uint32 squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> squareIB = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32));
		s_Renderer2DStorage->m_QuadVertexArray->SetIndexBuffer(squareIB);

		s_Renderer2DStorage->m_WhiteTexture = Texture2D::Create(1, 1);
		uint32 whiteTextureData = 0xffffffff;
		s_Renderer2DStorage->m_WhiteTexture->SetData(&whiteTextureData, sizeof(uint32));

		s_Renderer2DStorage->m_TextureShader = Shader::Create("../../../../../demo/data/assets/shaders/texture.glsl");
		s_Renderer2DStorage->m_TextureShader->Bind();
		s_Renderer2DStorage->m_TextureShader->SetInt("uTexture", 0);
	}

	void Renderer2D::Shutdown()
	{
		delete s_Renderer2DStorage;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& aCamera)
	{
		s_Renderer2DStorage->m_TextureShader->Bind();
		s_Renderer2DStorage->m_TextureShader->SetMatrix4("uViewProjection", aCamera.GetViewProjectionMatrix());
	}

	void Renderer2D::DrawQuad(const glm::vec2& aPosition, const glm::vec2& aSize, const glm::vec4& aColor)
	{
		DrawQuad({ aPosition.x, aPosition.y, 0.0f }, aSize, aColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& aPosition, const glm::vec2& aSize, const glm::vec4& aColor)
	{
		s_Renderer2DStorage->m_TextureShader->SetFloat4("uColor", aColor);
		s_Renderer2DStorage->m_TextureShader->SetFloat("uTiling", 1.0f);
		s_Renderer2DStorage->m_WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), aPosition) * glm::scale(glm::mat4(1.0f), { aSize.x, aSize.y, 1.0f });
		s_Renderer2DStorage->m_TextureShader->SetMatrix4("uTransform", transform);

		s_Renderer2DStorage->m_QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Renderer2DStorage->m_QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& aPosition, const glm::vec2& aSize, const std::shared_ptr<Texture2D>& aTexture, const glm::vec4& aColorTint, float aTilingScale)
	{
		DrawQuad({ aPosition.x, aPosition.y, 0.0f }, aSize, aTexture, aColorTint, aTilingScale);
	}

	void Renderer2D::DrawQuad(const glm::vec3& aPosition, const glm::vec2& aSize, const std::shared_ptr<Texture2D>& aTexture, const glm::vec4& aColorTint, float aTilingScale)
	{
		s_Renderer2DStorage->m_TextureShader->SetFloat4("uColor", aColorTint);
		s_Renderer2DStorage->m_TextureShader->SetFloat("uTilingScale", aTilingScale);
		aTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), aPosition) * glm::scale(glm::mat4(1.0f), { aSize.x, aSize.y, 1.0f });
		s_Renderer2DStorage->m_TextureShader->SetMatrix4("uTransform", transform);

		s_Renderer2DStorage->m_QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Renderer2DStorage->m_QuadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& aPosition, const glm::vec2& aSize, float aRotationRadiant, const glm::vec4& aColor)
	{
		DrawRotatedQuad({ aPosition.x, aPosition.y, 0.0f }, aSize, aRotationRadiant, aColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& aPosition, const glm::vec2& aSize, float aRotationRadiant, const glm::vec4& aColor)
	{
		s_Renderer2DStorage->m_TextureShader->SetFloat4("uColor", aColor);
		s_Renderer2DStorage->m_TextureShader->SetFloat("uTiling", 1.0f);
		s_Renderer2DStorage->m_WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), aPosition)
			* glm::rotate(glm::mat4(1.0f), aRotationRadiant, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { aSize.x, aSize.y, 1.0f });
		s_Renderer2DStorage->m_TextureShader->SetMatrix4("uTransform", transform);

		s_Renderer2DStorage->m_QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Renderer2DStorage->m_QuadVertexArray);
	}

}
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
	constexpr uint32 s_QuadVerticesCount{ 4 };
	constexpr uint32 s_QuadIndicesCount{ 6 };
	constexpr uint32 s_MaximumTextureSlots{ 32 };

	struct QuadVertex
	{
		glm::vec3 m_Position;
		glm::vec4 m_Color;
		glm::vec2 m_TextureCoord;
		float m_TextureIndex;
		float m_TilingScale;
	};

	struct Renderer2DData
	{
		const uint32 m_MaximumDrawCallQuads{ 10000 };
		const uint32 m_MaximumDrawCallVertices{ m_MaximumDrawCallQuads * s_QuadVerticesCount };
		const uint32 m_MaximumDrawCallIndices{ m_MaximumDrawCallQuads * s_QuadIndicesCount };

		std::array<std::shared_ptr<Texture2D>, s_MaximumTextureSlots> m_TextureSlots;
		uint32 m_TextureSlotIndex{ 1 }; // Default texture takes slot 0 for now;

		uint32 m_QuadIndexCount{ 0 };
		QuadVertex* m_QuadVertexBufferBase{ nullptr };
		QuadVertex* m_QuadVertexBufferPtr{ nullptr };

		std::shared_ptr<VertexArray> m_QuadVertexArray;
		std::shared_ptr<VertexBuffer> m_QuadVertexBuffer;
		std::shared_ptr<Shader> m_TextureShader;
		std::shared_ptr<Texture2D> m_WhiteTexture;
	};
	static Renderer2DData s_Renderer2DData;

	void Renderer2D::Init()
	{
		s_Renderer2DData.m_QuadVertexArray = VertexArray::Create();

		s_Renderer2DData.m_QuadVertexBuffer = VertexBuffer::Create(s_Renderer2DData.m_MaximumDrawCallVertices * sizeof(QuadVertex));
		s_Renderer2DData.m_QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "aPosition" },
			{ ShaderDataType::Float4, "aColor" },
			{ ShaderDataType::Float2, "aTextureCoord" },
			{ ShaderDataType::Float, "aTextureIndex" },
			{ ShaderDataType::Float, "aTilingScale" }
		});
		s_Renderer2DData.m_QuadVertexArray->AddVertexBuffer(s_Renderer2DData.m_QuadVertexBuffer);

		s_Renderer2DData.m_QuadVertexBufferBase = new QuadVertex[s_Renderer2DData.m_MaximumDrawCallVertices];

		// Used regular unique_ptr creation instead of CreateUnique to avoid each element being default initialized with a value
		std::unique_ptr<uint32[]> quadIndices = std::unique_ptr<uint32[]>{ new uint32[s_Renderer2DData.m_MaximumDrawCallIndices] };
		uint32 quadOffset = 0;
		for (uint32 i = 0; i < s_Renderer2DData.m_MaximumDrawCallIndices; i += 6)
		{
			quadIndices[i + 0] = quadOffset + 0;
			quadIndices[i + 1] = quadOffset + 1;
			quadIndices[i + 2] = quadOffset + 2;

			quadIndices[i + 3] = quadOffset + 2;
			quadIndices[i + 4] = quadOffset + 3;
			quadIndices[i + 5] = quadOffset + 0;
			
			quadOffset += 4;
		}
		std::shared_ptr<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices.get(), s_Renderer2DData.m_MaximumDrawCallIndices);
		s_Renderer2DData.m_QuadVertexArray->SetIndexBuffer(quadIB);

		s_Renderer2DData.m_WhiteTexture = Texture2D::Create(1, 1);
		uint32 whiteTextureData = 0xffffffff;
		s_Renderer2DData.m_WhiteTexture->SetData(&whiteTextureData, sizeof(uint32));

		int32 samples[s_MaximumTextureSlots];
		for (uint32 i = 0; i < s_MaximumTextureSlots; i++)
			samples[i] = i;

		s_Renderer2DData.m_TextureShader = Shader::Create("../../../../../demo/data/assets/shaders/texture.glsl");
		s_Renderer2DData.m_TextureShader->Bind();
		s_Renderer2DData.m_TextureShader->SetIntArray("uTexture", samples, s_MaximumTextureSlots);

		s_Renderer2DData.m_TextureSlots[0] = s_Renderer2DData.m_WhiteTexture;
	}

	void Renderer2D::Shutdown()
	{
	}

	void Renderer2D::BeginScene(const OrthographicCamera& aCamera)
	{
		s_Renderer2DData.m_TextureShader->Bind();
		s_Renderer2DData.m_TextureShader->SetMatrix4("uViewProjection", aCamera.GetViewProjectionMatrix());

		s_Renderer2DData.m_QuadIndexCount = 0;
		s_Renderer2DData.m_QuadVertexBufferPtr = s_Renderer2DData.m_QuadVertexBufferBase;

		s_Renderer2DData.m_TextureSlotIndex = 1;
	}

	void Renderer2D::EndScene()
	{
		uint32 dataSize = static_cast<uint32>((uint8*)s_Renderer2DData.m_QuadVertexBufferPtr - (uint8*)s_Renderer2DData.m_QuadVertexBufferBase);
		s_Renderer2DData.m_QuadVertexBuffer->SetData(s_Renderer2DData.m_QuadVertexBufferBase, dataSize);

		Flush();
	}

	void Renderer2D::Flush()
	{
		for (uint32 i = 0; i < s_Renderer2DData.m_TextureSlotIndex; i++)
			s_Renderer2DData.m_TextureSlots[i]->Bind(i);

		RenderCommand::DrawIndexed(s_Renderer2DData.m_QuadVertexArray, s_Renderer2DData.m_QuadIndexCount);
	}

	void Renderer2D::DrawQuad(const glm::vec2& aPosition, const glm::vec2& aSize, const glm::vec4& aColor)
	{
		DrawQuad({ aPosition.x, aPosition.y, 0.0f }, aSize, aColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& aPosition, const glm::vec2& aSize, const glm::vec4& aColor)
	{
		constexpr float defaultTextureIndex = 0.0f;
		constexpr float defaultTilingScale = 1.0f;

		s_Renderer2DData.m_QuadVertexBufferPtr->m_Position = aPosition;
		s_Renderer2DData.m_QuadVertexBufferPtr->m_Color = aColor;
		s_Renderer2DData.m_QuadVertexBufferPtr->m_TextureCoord = { 0.0f, 0.0f };
		s_Renderer2DData.m_QuadVertexBufferPtr->m_TextureIndex = defaultTextureIndex;
		s_Renderer2DData.m_QuadVertexBufferPtr->m_TilingScale = defaultTilingScale;
		s_Renderer2DData.m_QuadVertexBufferPtr++;

		s_Renderer2DData.m_QuadVertexBufferPtr->m_Position = { aPosition.x + aSize.x, aPosition.y, 0.0f };
		s_Renderer2DData.m_QuadVertexBufferPtr->m_Color = aColor;
		s_Renderer2DData.m_QuadVertexBufferPtr->m_TextureCoord = { 1.0f, 0.0f };
		s_Renderer2DData.m_QuadVertexBufferPtr->m_TextureIndex = defaultTextureIndex;
		s_Renderer2DData.m_QuadVertexBufferPtr->m_TilingScale = defaultTilingScale;
		s_Renderer2DData.m_QuadVertexBufferPtr++;

		s_Renderer2DData.m_QuadVertexBufferPtr->m_Position = { aPosition.x + aSize.x, aPosition.y + aSize.y, 0.0f };
		s_Renderer2DData.m_QuadVertexBufferPtr->m_Color = aColor;
		s_Renderer2DData.m_QuadVertexBufferPtr->m_TextureCoord = { 1.0f, 1.0f };
		s_Renderer2DData.m_QuadVertexBufferPtr->m_TextureIndex = defaultTextureIndex;
		s_Renderer2DData.m_QuadVertexBufferPtr->m_TilingScale = defaultTilingScale;
		s_Renderer2DData.m_QuadVertexBufferPtr++;

		s_Renderer2DData.m_QuadVertexBufferPtr->m_Position = { aPosition.x, aPosition.y + aSize.y, 0.0f };
		s_Renderer2DData.m_QuadVertexBufferPtr->m_Color = aColor;
		s_Renderer2DData.m_QuadVertexBufferPtr->m_TextureCoord = { 0.0f, 1.0f };
		s_Renderer2DData.m_QuadVertexBufferPtr->m_TextureIndex = defaultTextureIndex;
		s_Renderer2DData.m_QuadVertexBufferPtr->m_TilingScale = defaultTilingScale;
		s_Renderer2DData.m_QuadVertexBufferPtr++;

		s_Renderer2DData.m_QuadIndexCount += s_QuadIndicesCount;
#if SAMPO_OLD_RENDERING
 		s_Renderer2DData.m_TextureShader->SetFloat("uTiling", 1.0f);
 		s_Renderer2DData.m_WhiteTexture->Bind();
 
 		glm::mat4 transform = glm::translate(glm::mat4(1.0f), aPosition) * glm::scale(glm::mat4(1.0f), { aSize.x, aSize.y, 1.0f });
 		s_Renderer2DData.m_TextureShader->SetMatrix4("uTransform", transform);
 
 		s_Renderer2DData.m_QuadVertexArray->Bind();
 		RenderCommand::DrawIndexed(s_Renderer2DData.m_QuadVertexArray);
#endif // SAMPO_OLD_RENDERING
	}

	void Renderer2D::DrawQuad(const glm::vec2& aPosition, const glm::vec2& aSize, const std::shared_ptr<Texture2D>& aTexture, const glm::vec4& aColorTint, float aTilingScale)
	{
		DrawQuad({ aPosition.x, aPosition.y, 0.0f }, aSize, aTexture, aColorTint, aTilingScale);
	}

	void Renderer2D::DrawQuad(const glm::vec3& aPosition, const glm::vec2& aSize, const std::shared_ptr<Texture2D>& aTexture, const glm::vec4& aColorTint, float aTilingScale)
	{
		SAMPO_UNUSED(aTilingScale);
		SAMPO_UNUSED(aTexture);
		constexpr glm::vec4 defaultColor = { 1.0f, 1.0f, 1.0f, 1.0f };

		float textureIndex = 0.0f;
		for (uint32 i = 1; i < s_Renderer2DData.m_TextureSlotIndex; i++)
		{
			std::shared_ptr<Texture2D> texture = s_Renderer2DData.m_TextureSlots[i];
			if (!texture)
				break;

			if (texture == aTexture)
			{
				textureIndex = static_cast<float>(i);
				break;
			}
		}
		if (textureIndex == 0.0f)
		{
			s_Renderer2DData.m_TextureSlots[s_Renderer2DData.m_TextureSlotIndex] = aTexture;
			textureIndex = static_cast<float>(s_Renderer2DData.m_TextureSlotIndex);
			s_Renderer2DData.m_TextureSlotIndex++;
		}

		s_Renderer2DData.m_QuadVertexBufferPtr->m_Position = aPosition;
		s_Renderer2DData.m_QuadVertexBufferPtr->m_Color = aColorTint;
		s_Renderer2DData.m_QuadVertexBufferPtr->m_TextureCoord = { 0.0f, 0.0f };
		s_Renderer2DData.m_QuadVertexBufferPtr->m_TextureIndex = textureIndex;
		s_Renderer2DData.m_QuadVertexBufferPtr->m_TilingScale = aTilingScale;
		s_Renderer2DData.m_QuadVertexBufferPtr++;

		s_Renderer2DData.m_QuadVertexBufferPtr->m_Position = { aPosition.x + aSize.x, aPosition.y, 0.0f };
		s_Renderer2DData.m_QuadVertexBufferPtr->m_Color = aColorTint;
		s_Renderer2DData.m_QuadVertexBufferPtr->m_TextureCoord = { 1.0f, 0.0f };
		s_Renderer2DData.m_QuadVertexBufferPtr->m_TextureIndex = textureIndex;
		s_Renderer2DData.m_QuadVertexBufferPtr->m_TilingScale = aTilingScale;
		s_Renderer2DData.m_QuadVertexBufferPtr++;

		s_Renderer2DData.m_QuadVertexBufferPtr->m_Position = { aPosition.x + aSize.x, aPosition.y + aSize.y, 0.0f };
		s_Renderer2DData.m_QuadVertexBufferPtr->m_Color = aColorTint;
		s_Renderer2DData.m_QuadVertexBufferPtr->m_TextureCoord = { 1.0f, 1.0f };
		s_Renderer2DData.m_QuadVertexBufferPtr->m_TextureIndex = textureIndex;
		s_Renderer2DData.m_QuadVertexBufferPtr->m_TilingScale = aTilingScale;
		s_Renderer2DData.m_QuadVertexBufferPtr++;

		s_Renderer2DData.m_QuadVertexBufferPtr->m_Position = { aPosition.x, aPosition.y + aSize.y, 0.0f };
		s_Renderer2DData.m_QuadVertexBufferPtr->m_Color = aColorTint;
		s_Renderer2DData.m_QuadVertexBufferPtr->m_TextureCoord = { 0.0f, 1.0f };
		s_Renderer2DData.m_QuadVertexBufferPtr->m_TextureIndex = textureIndex;
		s_Renderer2DData.m_QuadVertexBufferPtr->m_TilingScale = aTilingScale;
		s_Renderer2DData.m_QuadVertexBufferPtr++;

		s_Renderer2DData.m_QuadIndexCount += s_QuadIndicesCount;
#if SAMPO_OLD_RENDERING
		s_Renderer2DData.m_TextureShader->SetFloat4("uColor", aColorTint);
		s_Renderer2DData.m_TextureShader->SetFloat("uTilingScale", aTilingScale);
		aTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), aPosition) * glm::scale(glm::mat4(1.0f), { aSize.x, aSize.y, 1.0f });
		s_Renderer2DData.m_TextureShader->SetMatrix4("uTransform", transform);

		s_Renderer2DData.m_QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Renderer2DData.m_QuadVertexArray);
#endif // SAMPO_OLD_RENDERING
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& aPosition, const glm::vec2& aSize, float aRotationRadiant, const glm::vec4& aColor)
	{
		DrawRotatedQuad({ aPosition.x, aPosition.y, 0.0f }, aSize, aRotationRadiant, aColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& aPosition, const glm::vec2& aSize, float aRotationRadiant, const glm::vec4& aColor)
	{
		s_Renderer2DData.m_TextureShader->SetFloat4("uColor", aColor);
		s_Renderer2DData.m_TextureShader->SetFloat("uTiling", 1.0f);
		s_Renderer2DData.m_WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), aPosition)
			* glm::rotate(glm::mat4(1.0f), aRotationRadiant, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { aSize.x, aSize.y, 1.0f });
		s_Renderer2DData.m_TextureShader->SetMatrix4("uTransform", transform);

		s_Renderer2DData.m_QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Renderer2DData.m_QuadVertexArray);
	}

}
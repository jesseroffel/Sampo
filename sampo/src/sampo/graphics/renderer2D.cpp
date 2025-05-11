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
		static const uint32 s_MaximumDrawCallQuads{ 1000 };
		static const uint32 s_MaximumDrawCallVertices{ s_MaximumDrawCallQuads * s_QuadVerticesCount };
		static const uint32 s_MaximumDrawCallIndices{ s_MaximumDrawCallQuads * s_QuadIndicesCount };

		std::array<std::shared_ptr<Texture2D>, s_MaximumTextureSlots> m_TextureSlots;
		uint32 m_TextureSlotIndex{ 1 }; // Default texture takes slot 0 for now;

		glm::vec4 m_QuadVertexPositions[4];
		uint32 m_QuadIndexCount{ 0 };
		QuadVertex* m_QuadVertexBufferBase{ nullptr };
		QuadVertex* m_QuadVertexBufferPtr{ nullptr };

		std::shared_ptr<VertexArray> m_QuadVertexArray;
		std::shared_ptr<VertexBuffer> m_QuadVertexBuffer;
		std::shared_ptr<Shader> m_TextureShader;
		std::shared_ptr<Texture2D> m_WhiteTexture;

		Renderer2D::Statistics m_Statistics;
	};
	static Renderer2DData s_Renderer2DData;

	void Renderer2D::Init()
	{
		s_Renderer2DData.m_QuadVertexArray = VertexArray::Create();

		s_Renderer2DData.m_QuadVertexBuffer = VertexBuffer::Create(s_Renderer2DData.s_MaximumDrawCallVertices * sizeof(QuadVertex));
		s_Renderer2DData.m_QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "aPosition" },
			{ ShaderDataType::Float4, "aColor" },
			{ ShaderDataType::Float2, "aTextureCoord" },
			{ ShaderDataType::Float, "aTextureIndex" },
			{ ShaderDataType::Float, "aTilingScale" }
			});
		s_Renderer2DData.m_QuadVertexArray->AddVertexBuffer(s_Renderer2DData.m_QuadVertexBuffer);

		s_Renderer2DData.m_QuadVertexBufferBase = new QuadVertex[s_Renderer2DData.s_MaximumDrawCallVertices];

		// Used regular unique_ptr creation instead of CreateUnique to avoid each element being default initialized with a value
		std::unique_ptr<uint32[]> quadIndices = std::unique_ptr<uint32[]>{ new uint32[s_Renderer2DData.s_MaximumDrawCallIndices] };
		uint32 quadOffset = 0;
		for (uint32 i = 0; i < s_Renderer2DData.s_MaximumDrawCallIndices; i += 6)
		{
			quadIndices[i + 0] = quadOffset + 0;
			quadIndices[i + 1] = quadOffset + 1;
			quadIndices[i + 2] = quadOffset + 2;

			quadIndices[i + 3] = quadOffset + 2;
			quadIndices[i + 4] = quadOffset + 3;
			quadIndices[i + 5] = quadOffset + 0;

			quadOffset += 4;
		}
		std::shared_ptr<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices.get(), s_Renderer2DData.s_MaximumDrawCallIndices);
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

		s_Renderer2DData.m_QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Renderer2DData.m_QuadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
		s_Renderer2DData.m_QuadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
		s_Renderer2DData.m_QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
	}

	void Renderer2D::BeginScene(const OrthographicCamera& aCamera)
	{
		s_Renderer2DData.m_TextureShader->Bind();
		s_Renderer2DData.m_TextureShader->SetMatrix4("uViewProjection", aCamera.GetViewProjectionMatrix());

		SetBlankBatchContext();
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
		s_Renderer2DData.m_Statistics.m_DrawCalls++;
	}

	void Renderer2D::DrawQuad(const glm::vec2& aPosition, const glm::vec2& aSize, const glm::vec4& aColor)
	{
		DrawQuad({ aPosition.x, aPosition.y, 0.0f }, aSize, aColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& aPosition, const glm::vec2& aSize, const glm::vec4& aColor)
	{
		if (s_Renderer2DData.m_QuadIndexCount >= Renderer2DData::s_MaximumDrawCallIndices)
			FlushAndReset();

		const glm::mat4 transform = glm::translate(glm::mat4(1.0f), aPosition)
			* glm::scale(glm::mat4(1.0f), { aSize.x, aSize.y, 1.0f });

		constexpr float defaultTextureIndex = 0.0f;
		constexpr float defaultTilingScale = 1.0f;

		SetBatchQuadVertexBuffer(transform, aColor, defaultTextureIndex, defaultTilingScale);
		s_Renderer2DData.m_QuadIndexCount += s_QuadIndicesCount;

		s_Renderer2DData.m_Statistics.m_QuadCount++;
	}

	void Renderer2D::DrawQuad(const glm::vec2& aPosition, const glm::vec2& aSize, const std::shared_ptr<Texture2D>& aTexture, const glm::vec4& aColor, float aTilingScale)
	{
		DrawQuad({ aPosition.x, aPosition.y, 0.0f }, aSize, aTexture, aColor, aTilingScale);
	}

	void Renderer2D::DrawQuad(const glm::vec3& aPosition, const glm::vec2& aSize, const std::shared_ptr<Texture2D>& aTexture, const glm::vec4& aColor, float aTilingScale)
	{
		if (s_Renderer2DData.m_QuadIndexCount >= Renderer2DData::s_MaximumDrawCallIndices)
			FlushAndReset();

		const glm::mat4 transform = glm::translate(glm::mat4(1.0f), aPosition)
			* glm::scale(glm::mat4(1.0f), { aSize.x, aSize.y, 1.0f });

		float textureIndex = GetTextureIndex(aTexture);

		SetBatchQuadVertexBuffer(transform, aColor, textureIndex, aTilingScale);
		s_Renderer2DData.m_QuadIndexCount += s_QuadIndicesCount;

		s_Renderer2DData.m_Statistics.m_QuadCount++;
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& aPosition, const glm::vec2& aSize, float aRotationRadians, const glm::vec4& aColor)
	{
		DrawRotatedQuad({ aPosition.x, aPosition.y, 0.0f }, aSize, aRotationRadians, aColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& aPosition, const glm::vec2& aSize, float aRotationRadians, const glm::vec4& aColor)
	{
		if (s_Renderer2DData.m_QuadIndexCount >= Renderer2DData::s_MaximumDrawCallIndices)
			FlushAndReset();

		const glm::mat4 transform = glm::translate(glm::mat4(1.0f), aPosition)
			* glm::rotate(glm::mat4(1.0f), aRotationRadians, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { aSize.x, aSize.y, 1.0f });

		constexpr float defaultTextureIndex = 0.0f;
		constexpr float defaultTilingScale = 1.0f;

		SetBatchQuadVertexBuffer(transform, aColor, defaultTextureIndex, defaultTilingScale);
		s_Renderer2DData.m_QuadIndexCount += s_QuadIndicesCount;

		s_Renderer2DData.m_Statistics.m_QuadCount++;
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& aPosition, const glm::vec2& aSize, float aRotationRadians, const std::shared_ptr<Texture2D>& aTexture, const glm::vec4& aColor, float aTilingScale)
	{
		DrawRotatedQuad({ aPosition.x, aPosition.y, 0.0f }, aSize, aRotationRadians, aTexture, aColor, aTilingScale);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& aPosition, const glm::vec2& aSize, float aRotationRadians, const std::shared_ptr<Texture2D>& aTexture, const glm::vec4& aColor, float aTilingScale)
	{
		if (s_Renderer2DData.m_QuadIndexCount >= Renderer2DData::s_MaximumDrawCallIndices)
			FlushAndReset();

		const glm::mat4 transform = glm::translate(glm::mat4(1.0f), aPosition)
			* glm::rotate(glm::mat4(1.0f), aRotationRadians, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { aSize.x, aSize.y, 1.0f });

		float textureIndex = GetTextureIndex(aTexture);

		SetBatchQuadVertexBuffer(transform, aColor, textureIndex, aTilingScale);
		s_Renderer2DData.m_QuadIndexCount += s_QuadIndicesCount;

		s_Renderer2DData.m_Statistics.m_QuadCount++;
	}

	void Renderer2D::FlushAndReset()
	{
		EndScene();

		SetBlankBatchContext();
	}

	void Renderer2D::SetBlankBatchContext()
	{
		s_Renderer2DData.m_QuadIndexCount = 0;
		s_Renderer2DData.m_QuadVertexBufferPtr = s_Renderer2DData.m_QuadVertexBufferBase;

		s_Renderer2DData.m_TextureSlotIndex = 1;
	}

	void Renderer2D::SetBatchQuadVertexBuffer(const glm::mat4& aTransform, const glm::vec4& aColor, float aTextureIndex, float aTilingScale)
	{
		s_Renderer2DData.m_QuadVertexBufferPtr->m_Position = aTransform * s_Renderer2DData.m_QuadVertexPositions[0];
		s_Renderer2DData.m_QuadVertexBufferPtr->m_Color = aColor;
		s_Renderer2DData.m_QuadVertexBufferPtr->m_TextureCoord = { 0.0f, 0.0f };
		s_Renderer2DData.m_QuadVertexBufferPtr->m_TextureIndex = aTextureIndex;
		s_Renderer2DData.m_QuadVertexBufferPtr->m_TilingScale = aTilingScale;
		s_Renderer2DData.m_QuadVertexBufferPtr++;

		s_Renderer2DData.m_QuadVertexBufferPtr->m_Position = aTransform * s_Renderer2DData.m_QuadVertexPositions[1];
		s_Renderer2DData.m_QuadVertexBufferPtr->m_Color = aColor;
		s_Renderer2DData.m_QuadVertexBufferPtr->m_TextureCoord = { 1.0f, 0.0f };
		s_Renderer2DData.m_QuadVertexBufferPtr->m_TextureIndex = aTextureIndex;
		s_Renderer2DData.m_QuadVertexBufferPtr->m_TilingScale = aTilingScale;
		s_Renderer2DData.m_QuadVertexBufferPtr++;

		s_Renderer2DData.m_QuadVertexBufferPtr->m_Position = aTransform * s_Renderer2DData.m_QuadVertexPositions[2];
		s_Renderer2DData.m_QuadVertexBufferPtr->m_Color = aColor;
		s_Renderer2DData.m_QuadVertexBufferPtr->m_TextureCoord = { 1.0f, 1.0f };
		s_Renderer2DData.m_QuadVertexBufferPtr->m_TextureIndex = aTextureIndex;
		s_Renderer2DData.m_QuadVertexBufferPtr->m_TilingScale = aTilingScale;
		s_Renderer2DData.m_QuadVertexBufferPtr++;

		s_Renderer2DData.m_QuadVertexBufferPtr->m_Position = aTransform * s_Renderer2DData.m_QuadVertexPositions[3];
		s_Renderer2DData.m_QuadVertexBufferPtr->m_Color = aColor;
		s_Renderer2DData.m_QuadVertexBufferPtr->m_TextureCoord = { 0.0f, 1.0f };
		s_Renderer2DData.m_QuadVertexBufferPtr->m_TextureIndex = aTextureIndex;
		s_Renderer2DData.m_QuadVertexBufferPtr->m_TilingScale = aTilingScale;
		s_Renderer2DData.m_QuadVertexBufferPtr++;
	}

	float Renderer2D::GetTextureIndex(const std::shared_ptr<Texture2D>& aTexture)
	{
		if (!aTexture)
			return 0.0f;

		for (uint32 i = 1; i < s_Renderer2DData.m_TextureSlotIndex; i++)
		{
			std::shared_ptr<Texture2D>& texture = s_Renderer2DData.m_TextureSlots[i];
			if (!texture)
				break;

			if (texture == aTexture)
				return static_cast<float>(i);
		}

		s_Renderer2DData.m_TextureSlots[s_Renderer2DData.m_TextureSlotIndex] = aTexture;
		float textureIndex = static_cast<float>(s_Renderer2DData.m_TextureSlotIndex);
		s_Renderer2DData.m_TextureSlotIndex++;
		return textureIndex;
	}

	const Renderer2D::Statistics& Renderer2D::GetStatistics()
	{
		return s_Renderer2DData.m_Statistics;
	}

	void Renderer2D::ResetStats()
	{
		memset(&s_Renderer2DData.m_Statistics, 0, sizeof(Renderer2D::Statistics));
	}
}

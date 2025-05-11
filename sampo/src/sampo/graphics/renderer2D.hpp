#pragma once

#include "camera.hpp"

namespace Sampo
{
	class Texture2D;

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown() {};

		static void BeginScene(const OrthographicCamera& aCamera);
		static void EndScene();
		static void Flush();

		static void DrawQuad(const glm::vec2& aPosition, const glm::vec2& aSize, const glm::vec4& aColor);
		static void DrawQuad(const glm::vec3& aPosition, const glm::vec2& aSize, const glm::vec4& aColor);
		static void DrawQuad(const glm::vec2& aPosition, const glm::vec2& aSize, const std::shared_ptr<Texture2D>& aTexture, const glm::vec4& aColor = { 1.0f, 1.0f, 1.0f, 1.0f }, float aTilingScale = 1.0f);
		static void DrawQuad(const glm::vec3& aPosition, const glm::vec2& aSize, const std::shared_ptr<Texture2D>& aTexture, const glm::vec4& aColor = { 1.0f, 1.0f, 1.0f, 1.0f }, float aTilingScale = 1.0f);

		static void DrawRotatedQuad(const glm::vec2& aPosition, const glm::vec2& aSize, float aRotationRadians, const glm::vec4& aColor);
		static void DrawRotatedQuad(const glm::vec3& aPosition, const glm::vec2& aSize, float aRotationRadians, const glm::vec4& aColor);
		static void DrawRotatedQuad(const glm::vec2& aPosition, const glm::vec2& aSize, float aRotationRadians, const std::shared_ptr<Texture2D>& aTexture, const glm::vec4& aColor = { 1.0f, 1.0f, 1.0f, 1.0f }, float aTilingScale = 1.0f);
		static void DrawRotatedQuad(const glm::vec3& aPosition, const glm::vec2& aSize, float aRotationRadians, const std::shared_ptr<Texture2D>& aTexture, const glm::vec4& aColor = { 1.0f, 1.0f, 1.0f, 1.0f }, float aTilingScale = 1.0f);

		struct Statistics
		{
			uint32 m_DrawCalls{ 0 };
			uint32 m_QuadCount{ 0 };

			uint32 GetTotalVertexCount() const { return m_QuadCount * 4; }
			uint32 GetTotalIndicesCount() const { return m_QuadCount * 6; }
		};
		static const Statistics& GetStatistics();
		static void ResetStats();

	private:
		static void FlushAndReset();
		static void SetBlankBatchContext();
		static void SetBatchQuadVertexBuffer(const glm::mat4& aTransform, const glm::vec4& aColor, float aTextureIndex, float aTilingScale);
		static float GetTextureIndex(const std::shared_ptr<Texture2D>& aTexture);
	};
}
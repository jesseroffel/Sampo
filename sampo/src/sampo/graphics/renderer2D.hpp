#pragma once

#include "camera.hpp"

namespace Sampo
{
	class Texture2D;

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& aCamera);
		static void EndScene();
		static void Flush();

		static void DrawQuad(const glm::vec2& aPosition, const glm::vec2& aSize, const glm::vec4& aColor);
		static void DrawQuad(const glm::vec3& aPosition, const glm::vec2& aSize, const glm::vec4& aColor);
		static void DrawQuad(const glm::vec2& aPosition, const glm::vec2& aSize, const std::shared_ptr<Texture2D>& aTexture, const glm::vec4& aColorTint = { 1.0f, 1.0f, 1.0f, 1.0f }, float aTilingScale = 1.0f);
		static void DrawQuad(const glm::vec3& aPosition, const glm::vec2& aSize, const std::shared_ptr<Texture2D>& aTexture, const glm::vec4& aColorTint = { 1.0f, 1.0f, 1.0f, 1.0f }, float aTilingScale = 1.0f);

		static void DrawRotatedQuad(const glm::vec2& aPosition, const glm::vec2& aSize, float aRotationRadiant, const glm::vec4& aColor);
		static void DrawRotatedQuad(const glm::vec3& aPosition, const glm::vec2& aSize, float aRotationRadiant, const glm::vec4& aColor);
	};
}
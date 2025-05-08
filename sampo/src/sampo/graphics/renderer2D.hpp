#pragma once

#include "camera.hpp"

namespace Sampo
{
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& aCamera);
		static void EndScene() {};

		static void DrawQuad(const glm::vec2& aPosition, const glm::vec2& aSize, const glm::vec4& aColor);
		static void DrawQuad(const glm::vec3& aPosition, const glm::vec2& aSize, const glm::vec4& aColor);
	};
}
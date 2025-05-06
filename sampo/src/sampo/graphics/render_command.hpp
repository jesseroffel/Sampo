#pragma once

#include <glm/glm.hpp>

namespace Sampo
{
	class RendererAPI;
	class VertexArray;

	class RenderCommand
	{
	public:
		static void Init();

		static void SetViewport(uint32 aViewportX, uint32 aViewportY, uint32 aWidth, uint32 aHeight);

		static void SetClearColor(const glm::vec4& aColor);
		static void Clear();

		static void DrawIndexed(const std::shared_ptr<VertexArray>& aVertexArray);

		static RendererAPI* s_RendererAPI;
	};
}
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

		static void SetClearColor(const glm::vec4& aColor);
		static void Clear();

		static void DrawIndexed(const std::shared_ptr<VertexArray>& aVertexArray);

		static RendererAPI* s_RendererAPI;
	};
}
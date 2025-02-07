#pragma once

#include "renderer_api.hpp"

namespace Sampo
{
	class VertexArray;

	class Renderer
	{
	public:
		static void BeginScene() {};
		static void EndScene() {};

		static void Submit(const std::shared_ptr<VertexArray>& aVertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}
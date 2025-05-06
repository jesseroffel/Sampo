#pragma once

#include <glm/glm.hpp>

namespace Sampo
{
	class VertexArray;

	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL
		};

		virtual void Init() = 0;
		virtual void SetViewport(uint32 aViewportX, uint32 aViewportY, uint32 aWidth, uint32 aHeight) = 0;
		virtual void SetClearColor(const glm::vec4& aColor) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& aVertexArray) = 0;

		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};
}
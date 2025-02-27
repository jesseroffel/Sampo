#pragma once

#include "sampo/graphics/renderer_api.hpp"

namespace Sampo
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual ~OpenGLRendererAPI() = default;

		void Init() override;
		void SetClearColor(const glm::vec4& aColor) override;
		void Clear() override;

		void DrawIndexed(const std::shared_ptr<VertexArray>& aVertexArray) override;
	};
}
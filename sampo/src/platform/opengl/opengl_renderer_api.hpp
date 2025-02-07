#pragma once

#include "sampo/graphics/renderer_api.hpp"

namespace Sampo
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual ~OpenGLRendererAPI() = default;
		virtual void SetClearColor(const glm::vec4& aColor) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& aVertexArray) override;
	};
}
#include "sampo_pch.hpp"
#include "render_command.hpp"

#include "vertex_array.hpp"

#include "platform/opengl/opengl_renderer_api.hpp"

namespace Sampo
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

	void RenderCommand::SetClearColor(const glm::vec4& aColor)
	{
		s_RendererAPI->SetClearColor(aColor);
	}

	void RenderCommand::Clear()
	{
		s_RendererAPI->Clear();
	}

	void RenderCommand::DrawIndexed(const std::shared_ptr<VertexArray>& aVertexArray)
	{
		s_RendererAPI->DrawIndexed(aVertexArray);
	}

}
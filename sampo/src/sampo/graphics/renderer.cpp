#include "sampo_pch.hpp"
#include "renderer.hpp"

#include "vertex_array.hpp"
#include "render_command.hpp"

namespace Sampo
{
	void Renderer::Submit(const std::shared_ptr<VertexArray>& aVertexArray)
	{
		aVertexArray->Bind();
		RenderCommand::DrawIndexed(aVertexArray);
	}
}
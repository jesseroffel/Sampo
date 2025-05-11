#include "sampo_pch.hpp"
#include "render_command.hpp"

#include "vertex_array.hpp"

#ifdef SAMPO_PLATFORM_WINDOWS
	#include "platform/opengl/opengl_renderer_api.hpp"
#endif // SAMPO_PLATFORM_WINDOWS

namespace Sampo
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

	void RenderCommand::Init()
	{
		s_RendererAPI->Init();
	}

	void RenderCommand::SetViewport(uint32 aViewportX, uint32 aViewportY, uint32 aWidth, uint32 aHeight)
	{
		s_RendererAPI->SetViewport(aViewportX, aViewportY, aWidth, aHeight);
	}

	void RenderCommand::SetClearColor(const glm::vec4& aColor)
	{
		s_RendererAPI->SetClearColor(aColor);
	}

	void RenderCommand::Clear()
	{
		s_RendererAPI->Clear();
	}

	void RenderCommand::DrawIndexed(const std::shared_ptr<VertexArray>& aVertexArray, uint32 anIndexCount)
	{
		s_RendererAPI->DrawIndexed(aVertexArray, anIndexCount);
	}

}
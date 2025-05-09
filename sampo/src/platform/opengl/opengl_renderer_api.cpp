#include "sampo_pch.hpp"
#include "opengl_renderer_api.hpp"

#include "sampo/graphics/buffer.hpp"

#include "opengl_vertex_array.hpp"

#include <glad/glad.h>

namespace Sampo
{
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	void OpenGLRendererAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::SetViewport(uint32 aViewportX, uint32 aViewportY, uint32 aWidth, uint32 aHeight)
	{
		glViewport(aViewportX, aViewportY, aWidth, aHeight);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& aColor)
	{
		glClearColor(aColor.r, aColor.g, aColor.b, aColor.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& aVertexArray)
	{
		glDrawElements(GL_TRIANGLES, aVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}
#include "sampo_pch.hpp"
#include "vertex_array.hpp"

#include "buffer.hpp"
#include "renderer.hpp"

#include "platform/opengl/opengl_vertex_array.hpp"	// TODO - Add platform ifdefs

namespace Sampo
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: SAMPO_ASSERT_MSG(false, "Headless API not supported!"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLVertexArray();
		}

		SAMPO_ASSERT_MSG(false, "API Version not supported!");
		return nullptr;
	}
}
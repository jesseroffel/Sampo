#include "sampo_pch.hpp"
#include "vertex_array.hpp"

#include "buffer.hpp"
#include "renderer.hpp"

#if SAMPO_PLATFORM_WINDOWS
	#include "platform/opengl/opengl_vertex_array.hpp"
#endif // SAMPO_PLATFORM_WINDOWS

namespace Sampo
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: SAMPO_ASSERT_MSG(false, "Headless API not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}

		SAMPO_ASSERT_MSG(false, "API Version not supported!");
		return nullptr;
	}
}
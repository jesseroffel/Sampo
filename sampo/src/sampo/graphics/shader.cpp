#include "sampo_pch.hpp"
#include "shader.hpp"

#include "renderer.hpp"

#if SAMPO_PLATFORM_WINDOWS
	#include "platform/opengl/opengl_shader.hpp"
#endif // SAMPO_PLATFORM_WINDOWS

namespace Sampo
{
	Shader* Shader::Create(const std::string& aVertexSource, const std::string& aFragmentSource)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: SAMPO_ASSERT_MSG(false, "Headless API not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLShader(aVertexSource, aFragmentSource);
		}

		SAMPO_ASSERT_MSG(false, "API Version not supported!");
		return nullptr;
	}
}
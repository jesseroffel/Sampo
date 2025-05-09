#include "sampo_pch.hpp"
#include "texture.hpp"

#include "renderer.hpp"

#ifdef SAMPO_PLATFORM_WINDOWS
	#include "opengl/opengl_texture.hpp"
#endif // SAMPO_PLATFORM_WINDOWS

namespace Sampo
{
	std::shared_ptr<Texture2D> Texture2D::Create(uint32 aWidth, uint32 aHeight)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: SAMPO_ASSERT_MSG(false, "Headless API not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateShared<OpenGLTexture2D>(aWidth, aHeight);
		}

		SAMPO_ASSERT_MSG(false, "API Version not supported!");
		return nullptr;
	}

	std::shared_ptr<Texture2D> Texture2D::Create(const std::string& aFilepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: SAMPO_ASSERT_MSG(false, "Headless API not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateShared<OpenGLTexture2D>(aFilepath);
		}

		SAMPO_ASSERT_MSG(false, "API Version not supported!");
		return nullptr;
	}
}
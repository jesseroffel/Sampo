#include "sampo_pch.hpp"
#include "opengl_texture.hpp"

#include <stb_image.h>
#include <glad/glad.h>

namespace Sampo
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& aFilepath)
		: m_Filepath(aFilepath)
	{
		stbi_set_flip_vertically_on_load(true);

		int width, height, channels = 0;
		stbi_uc* imageData = stbi_load(m_Filepath.c_str(), &width, &height, &channels, 0);
		SAMPO_ASSERT_MSG(imageData, "Failed to load image data!");

		m_TextureSize.x = width;
		m_TextureSize.y = height;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, GL_RGB8, m_TextureSize.x, m_TextureSize.y);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_TextureSize.x, m_TextureSize.y, GL_RGB, GL_UNSIGNED_BYTE, imageData);

		stbi_image_free(imageData);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(uint32 aTextureSlot) const
	{
		glBindTextureUnit(aTextureSlot, m_RendererID);
	}
}
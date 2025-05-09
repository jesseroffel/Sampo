#include "sampo_pch.hpp"
#include "opengl_texture.hpp"

#include <stb_image.h>

namespace Sampo
{
	OpenGLTexture2D::OpenGLTexture2D(uint32 aWidth, uint32 aHeight)
		: m_TextureSize(aWidth, aHeight)
	{
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_TextureSize.x, m_TextureSize.y);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& aFilepath)
		: m_Filepath(aFilepath)
	{
		stbi_set_flip_vertically_on_load(true);

		int width, height, channels = 0;
		stbi_uc* imageData = stbi_load(m_Filepath.c_str(), &width, &height, &channels, 0);
		SAMPO_ASSERT_MSG(imageData, "Failed to load image data!");

		m_TextureSize.x = width;
		m_TextureSize.y = height;

		const GLenum internalFormat = channels == 3 ? GL_RGB8 : channels == 4 ? GL_RGBA8 : 0;
		const GLenum dataFormat = channels == 3 ? GL_RGB : channels == 4 ? GL_RGBA : 0;
		SAMPO_ASSERT_MSG(internalFormat & dataFormat, "Unsupported texture format!");
		
		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_TextureSize.x, m_TextureSize.y);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_TextureSize.x, m_TextureSize.y, m_DataFormat, GL_UNSIGNED_BYTE, imageData);

		stbi_image_free(imageData);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::SetData(void* aData, uint32 aSize)
	{
		SAMPO_ASSERT_MSG(aSize < static_cast<uint32>((m_TextureSize.x + m_TextureSize.y) * GL_RGB8), "Provided size is smaller than expected data size!");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_TextureSize.x, m_TextureSize.y, m_DataFormat, GL_UNSIGNED_BYTE, aData);
	}

	void OpenGLTexture2D::Bind(uint32 aTextureSlot) const
	{
		glBindTextureUnit(aTextureSlot, m_RendererID);
	}
}
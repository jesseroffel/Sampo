#pragma once
#include "sampo/graphics/texture.hpp"

#include <glm/glm.hpp>
#include <glad/glad.h>

namespace Sampo
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(uint32 aWidth, uint32 aHeight);
		OpenGLTexture2D(const std::string& aFilepath);
		~OpenGLTexture2D();

		virtual uint32 GetWidth() const override { return m_TextureSize.x; }
		virtual uint32 GetHeight() const override { return m_TextureSize.y; }

		virtual void SetData(void* aData, uint32 aSize) override;

		virtual void Bind(uint32 aTextureSlot) const override;
	private:
		std::string m_Filepath;
		glm::ivec2 m_TextureSize{ 0, 0 };
		uint32 m_RendererID{ uint32_max };
		GLenum m_InternalFormat{ uint32_max };
		GLenum m_DataFormat{ uint32_max };
	};
}
#pragma once
#include "sampo/graphics/texture.hpp"

#include <glm/glm.hpp>

namespace Sampo
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& aFilepath);
		~OpenGLTexture2D();

		uint32 GetWidth() const override { return m_TextureSize.x; }
		uint32 GetHeight() const override { return m_TextureSize.y; }

		void Bind(uint32 aTextureSlot) const override;
	private:
		std::string m_Filepath;
		glm::ivec2 m_TextureSize{ 0, 0 };
		uint32 m_RendererID{ uint32_max };
	};
}
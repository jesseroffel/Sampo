#pragma once
#include "sampo/graphics/shader.hpp"

#include <glm/glm.hpp>

namespace Sampo
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& aVertexSource, const std::string& aFragmentSource);
		virtual ~OpenGLShader();

		void Bind() const override;
		void Unbind() const override;

		void UploadUniformInt(const std::string& aName, int aValue);

		void UploadUniformFloat(const std::string& aName, float aValue);
		void UploadUniformFloat2(const std::string& aName, const glm::vec2& aValue);
		void UploadUniformFloat3(const std::string& aName, const glm::vec3& aValue);
		void UploadUniformFloat4(const std::string& aName, const glm::vec4& aValue);

		void UploadUniformMatrix3(const std::string& aName, const glm::mat3& aValue);
		void UploadUniformMatrix4(const std::string& aName, const glm::mat4& aValue);
	private:
		uint32 m_RendererID{ uint32_max };
	};
}
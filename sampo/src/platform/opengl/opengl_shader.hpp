#pragma once
#include "sampo/graphics/shader.hpp"

#include <glm/glm.hpp>
#include <glad/glad.h>

namespace Sampo
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& aFilepath);
		OpenGLShader(const std::string& aName, const std::string& aVertexSource, const std::string& aFragmentSource);
		virtual ~OpenGLShader();

		void Bind() const override;
		void Unbind() const override;

		void SetFloat3(const std::string& aName, const glm::vec3& aValue) override;
		void SetFloat4(const std::string& aName, const glm::vec4& aValue) override;
		void SetMatrix4(const std::string& aName, const glm::mat4& aValue) override;

		virtual const std::string& GetName() const override { return m_Name; }

		void UploadUniformInt(const std::string& aName, int aValue);

		void UploadUniformFloat(const std::string& aName, float aValue);
		void UploadUniformFloat2(const std::string& aName, const glm::vec2& aValue);
		void UploadUniformFloat3(const std::string& aName, const glm::vec3& aValue);
		void UploadUniformFloat4(const std::string& aName, const glm::vec4& aValue);

		void UploadUniformMatrix3(const std::string& aName, const glm::mat3& aValue);
		void UploadUniformMatrix4(const std::string& aName, const glm::mat4& aValue);
	private:
		std::string ReadFile(const std::string& aFilepath);
		std::unordered_map<GLenum, std::string> PreprocessFile(const std::string& aSourceString);
		void Compile(const std::unordered_map<GLenum, std::string>& aShaderSources);

		std::string m_Name;
		uint32 m_RendererID{ uint32_max };
	};
}
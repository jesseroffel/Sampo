#include "sampo_pch.hpp"
#include "opengl_shader.hpp"

#include <filesystem>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Sampo
{
	static GLenum ShaderTypeFromString(const std::string& aGLType)
	{
		if (aGLType == "vertex")
			return GL_VERTEX_SHADER;
		if (aGLType == "fragment")
			return GL_FRAGMENT_SHADER;

		SAMPO_ASSERT_MSG(false, "Unknown/unimplemented shader type.");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& aFilepath)
	{
		const std::string fileContents = ReadFile(aFilepath);
		if (fileContents.empty())
			return;

		const std::unordered_map<GLenum, std::string> sources = PreprocessFile(fileContents);
		Compile(sources);

		const std::filesystem::path path = aFilepath;
		m_Name = path.stem().string();
	}

	OpenGLShader::OpenGLShader(const std::string& aName, const std::string& aVertexSource, const std::string& aFragmentSource)
		: m_Name(aName)
	{
		std::unordered_map<GLenum, std::string> shaderSources;
		shaderSources[GL_VERTEX_SHADER] = aVertexSource;
		shaderSources[GL_FRAGMENT_SHADER] = aFragmentSource;
		Compile(shaderSources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformInt(const std::string& aName, int aValue)
	{
		GLint location = glGetUniformLocation(m_RendererID, aName.c_str());
		glUniform1i(location, aValue);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& aName, float aValue)
	{
		GLint location = glGetUniformLocation(m_RendererID, aName.c_str());
		glUniform1f(location, aValue);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& aName, const glm::vec2& aValue)
	{
		GLint location = glGetUniformLocation(m_RendererID, aName.c_str());
		glUniform2f(location, aValue.x, aValue.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& aName, const glm::vec3& aValue)
	{
		GLint location = glGetUniformLocation(m_RendererID, aName.c_str());
		glUniform3f(location, aValue.x, aValue.y, aValue.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& aName, const glm::vec4& aValue)
	{
		GLint location = glGetUniformLocation(m_RendererID, aName.c_str());
		glUniform4f(location, aValue.x, aValue.y, aValue.z, aValue.w);
	}

	void OpenGLShader::UploadUniformMatrix3(const std::string& aName, const glm::mat3& aValue)
	{
		GLint location = glGetUniformLocation(m_RendererID, aName.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(aValue));
	}

	void OpenGLShader::UploadUniformMatrix4(const std::string& aName, const glm::mat4& aValue)
	{
		GLint location = glGetUniformLocation(m_RendererID, aName.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(aValue));
	}

	std::string OpenGLShader::ReadFile(const std::string& aFilepath)
	{
		std::string result;

		std::ifstream instream(aFilepath, std::ios::in | std::ios::binary);
		if (!instream)
		{
			SAMPO_CORE_ERROR("Could not open shader file {0}.", aFilepath);
			return result;
		}

		instream.seekg(0, std::ios::end);
		result.resize(instream.tellg());
		instream.seekg(0, std::ios::beg);
		instream.read(&result[0], result.size());
		instream.close();
		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreprocessFile(const std::string& aSourceString)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		static const char* typeKeyword = "#type";
		const size_t typeKeywordLength = strlen(typeKeyword);
		size_t filePosition = aSourceString.find(typeKeyword, 0);
		while (filePosition != std::string::npos)
		{
			const size_t endOfLine = aSourceString.find_first_of("\r\n", filePosition);
			SAMPO_ASSERT_MSG(endOfLine != std::string::npos, "Syntax error");

			const size_t beginKeyword = filePosition + typeKeywordLength + 1;
			const std::string shaderType = aSourceString.substr(beginKeyword, endOfLine - beginKeyword);
			SAMPO_ASSERT_MSG(ShaderTypeFromString(shaderType), "Invalid shader type specified");

			const size_t nextLinePos = aSourceString.find_first_not_of("\r\n", endOfLine);
			SAMPO_ASSERT_MSG(nextLinePos != std::string::npos, "Syntax error");
			filePosition = aSourceString.find(typeKeyword, nextLinePos);

			std::string& shaderSource = shaderSources[ShaderTypeFromString(shaderType)];
			shaderSource = (filePosition == std::string::npos) ? aSourceString.substr(nextLinePos) : aSourceString.substr(nextLinePos, filePosition - nextLinePos);
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& aShaderSources)
	{
		SAMPO_ASSERT_MSG(aShaderSources.size() <= 2, "We only support up to two shaders, needs increase if ever triggered.");
		GLuint programID = glCreateProgram();

		std::array<GLuint, 2> glShaderIDs;
		int glShaderIndex = 0;
		for (auto&& [key, value] : aShaderSources)
		{
			GLenum shaderType = key;
			const std::string& source = value;

			GLuint shader = glCreateShader(shaderType);

			const GLchar* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				SAMPO_CORE_ERROR("{0}", infoLog.data());
				SAMPO_ASSERT_MSG(false, "Shader compilation failed!");
				return;
			}

			glAttachShader(programID, shader);
			glShaderIDs[glShaderIndex++] = shader;
		}

		glLinkProgram(programID);

		GLint isLinked = 0;
		glGetProgramiv(programID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(programID, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(programID);

			for (const GLenum shaderID : glShaderIDs)
				glDeleteShader(shaderID);

			SAMPO_CORE_ERROR("{0}", infoLog.data());
			SAMPO_ASSERT_MSG(false, "Shader linking failed!");
			return;
		}

		for (const GLenum shaderID : glShaderIDs)
			glDetachShader(m_RendererID, shaderID);

		m_RendererID = programID;
	}
}
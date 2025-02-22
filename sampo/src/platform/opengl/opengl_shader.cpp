#include "sampo_pch.hpp"
#include "opengl_shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

namespace Sampo
{
	OpenGLShader::OpenGLShader(const std::string& aVertexSource, const std::string& aFragmentSource)
	{
		// Read our shaders into the appropriate buffers
		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = aVertexSource.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			SAMPO_CORE_ERROR("{0}", infoLog.data());
			SAMPO_ASSERT_MSG(false, "Vertex shader compilation failed!");
			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = aFragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			SAMPO_CORE_ERROR("{0}", infoLog.data());
			SAMPO_ASSERT_MSG(false, "Fragment shader compilation failed!");
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_RendererID = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);

		// Link our program
		glLinkProgram(m_RendererID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_RendererID);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			SAMPO_CORE_ERROR("{0}", infoLog.data());
			SAMPO_ASSERT_MSG(false, "Shader linking failed!");
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(m_RendererID, vertexShader);
		glDetachShader(m_RendererID, fragmentShader);
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
}
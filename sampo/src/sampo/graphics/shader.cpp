#include "sampo_pch.hpp"
#include "shader.hpp"

#include "renderer.hpp"

#if SAMPO_PLATFORM_WINDOWS
	#include "platform/opengl/opengl_shader.hpp"
#endif // SAMPO_PLATFORM_WINDOWS

namespace Sampo
{
	std::shared_ptr<Shader> Shader::Create(const std::string& aFilepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: SAMPO_ASSERT_MSG(false, "Headless API not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateShared<OpenGLShader>(aFilepath);
		}

		SAMPO_ASSERT_MSG(false, "API Version not supported!");
		return nullptr;
	}

	std::shared_ptr<Shader> Shader::Create(const std::string& aName, const std::string& aVertexSource, const std::string& aFragmentSource)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: SAMPO_ASSERT_MSG(false, "Headless API not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateShared<OpenGLShader>(aName, aVertexSource, aFragmentSource);
		}

		SAMPO_ASSERT_MSG(false, "API Version not supported!");
		return nullptr;
	}


	void ShaderLibrary::Add(const std::shared_ptr<Shader>& aShader)
	{
		Add(aShader->GetName(), aShader);
	}

	void ShaderLibrary::Add(const std::string& aName, const std::shared_ptr<Shader>& aShader)
	{
		SAMPO_ASSERT_MSG(!Exists(aName), "A Shader is already registered with this name!");
		m_Shaders[aName] = aShader;
	}

	std::shared_ptr<Shader> ShaderLibrary::Load(const std::string& aFilepath)
	{
		std::shared_ptr<Shader> shader = Shader::Create(aFilepath);
		Add(shader);
		return shader;
	}

	std::shared_ptr<Shader> ShaderLibrary::Load(const std::string& aName, const std::string& aFilepath)
	{
		std::shared_ptr<Shader> shader = Shader::Create(aFilepath);
		Add(aName, shader);
		return shader;
	}

	std::shared_ptr<Shader> ShaderLibrary::Get(const std::string& aName)
	{
		SAMPO_ASSERT_MSG(Exists(aName), "No Shader is registered with the provided name!");
		return m_Shaders[aName];
	}

	bool ShaderLibrary::Exists(const std::string& aName) const
	{
		return m_Shaders.find(aName) != m_Shaders.end();
	}

}
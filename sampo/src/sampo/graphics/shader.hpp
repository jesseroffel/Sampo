#pragma once

#include <glm/glm.hpp>

namespace Sampo
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		
		virtual void SetInt(const std::string& aName, int aValue) = 0;
		virtual void SetFloat(const std::string& aName, float aValue) = 0;
		virtual void SetFloat2(const std::string& aName, const glm::vec2& aValue) = 0;
		virtual void SetFloat3(const std::string& aName, const glm::vec3& aValue) = 0;
		virtual void SetFloat4(const std::string& aName, const glm::vec4& aValue) = 0;
		virtual void SetMatrix4(const std::string& aName, const glm::mat4& aValue) = 0;

		virtual const std::string& GetName() const = 0;

		static std::shared_ptr<Shader> Create(const std::string& aFilepath);
		static std::shared_ptr<Shader> Create(const std::string& aName, const std::string& aVertexSource, const std::string& aFragmentSource);
	private:
		uint32 m_RendererID{ uint32_max };
	};

	class ShaderLibrary
	{
	public:
		void Add(const std::shared_ptr<Shader>& aShader);
		void Add(const std::string& aName, const std::shared_ptr<Shader>& aShader);
		std::shared_ptr<Shader> Load(const std::string& aFilepath);
		std::shared_ptr<Shader> Load(const std::string& aName, const std::string& aFilepath);

		std::shared_ptr<Shader> Get(const std::string& aName);

		bool Exists(const std::string& aName) const;
	private:
		std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
	};
}
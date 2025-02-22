#pragma once

namespace Sampo
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(const std::string& aVertexSource, const std::string& aFragmentSource);
	private:
		uint32 m_RendererID{ uint32_max };
	};
}
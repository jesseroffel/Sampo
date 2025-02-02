#pragma once

namespace Sampo
{
	class Shader
	{
	public:
		Shader(const std::string& aVertexSource, const std::string& aFragmentSource);
		~Shader();

		void Bind() const;
		void Unbind() const;
	private:
		uint32 m_RendererID;
	};
}
#pragma once

#include <glm/glm.hpp>

namespace Sampo
{
	class Shader
	{
	public:
		Shader(const std::string& aVertexSource, const std::string& aFragmentSource);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformMat4(const std::string& aName, const glm::mat4& aMatrix);
	private:
		uint32 m_RendererID;
	};
}
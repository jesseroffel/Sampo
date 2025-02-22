#include "sampo_pch.hpp"
#include "renderer.hpp"

#include "camera.hpp"
#include "shader.hpp"
#include "render_command.hpp"
#include "vertex_array.hpp"

#if SAMPO_PLATFORM_WINDOWS
	#include "platform/opengl/opengl_shader.hpp"
#endif // SAMPO_PLATFORM_WINDOWS

namespace Sampo
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& aCamera)
	{
		m_SceneData->m_ViewProjectionMatrix = aCamera.GetViewProjectionMatrix();
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& aShader, const std::shared_ptr<VertexArray>& aVertexArray, const glm::mat4& aTransform)
	{
		aShader->Bind();

		std::shared_ptr<OpenGLShader> squareShader = std::dynamic_pointer_cast<OpenGLShader>(aShader);
		squareShader->UploadUniformMatrix4("uViewProjection", m_SceneData->m_ViewProjectionMatrix);
		squareShader->UploadUniformMatrix4("uTransform", aTransform);

		aVertexArray->Bind();
		RenderCommand::DrawIndexed(aVertexArray);
	}
}
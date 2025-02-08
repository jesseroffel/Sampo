#include "sampo_pch.hpp"
#include "renderer.hpp"

#include "camera.hpp"
#include "shader.hpp"
#include "render_command.hpp"
#include "vertex_array.hpp"

namespace Sampo
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& aCamera)
	{
		m_SceneData->m_ViewProjectionMatrix = aCamera.GetViewProjectionMatrix();
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& aShader, const std::shared_ptr<VertexArray>& aVertexArray)
	{
		aShader->Bind();
		aShader->UploadUniformMat4("uViewProjection", m_SceneData->m_ViewProjectionMatrix);

		aVertexArray->Bind();
		RenderCommand::DrawIndexed(aVertexArray);
	}
}
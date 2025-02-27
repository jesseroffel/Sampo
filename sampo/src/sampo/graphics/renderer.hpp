#pragma once

#include "renderer_api.hpp"

namespace Sampo
{
	class OrthographicCamera;
	class Shader;
	class VertexArray;

	class Renderer
	{
	public:
		static void Init();

		static void BeginScene(OrthographicCamera& aCamera);
		static void EndScene() {};

		static void Submit(const std::shared_ptr<Shader>& aShader, const std::shared_ptr<VertexArray>& aVertexArray, const glm::mat4& aTransform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 m_ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}
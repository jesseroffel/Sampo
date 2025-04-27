#pragma once
#include "sampo.hpp"

namespace Sampo
{
	class Keyboard;
	class Event;
}

class DemoLayer : public Sampo::Layer
{
public:
	DemoLayer(const glm::vec2& aWindowSize = {1280.0f, 720.0f});
	~DemoLayer() = default;

	void OnAttach() override;
	void OnUpdate(Sampo::Timestep aDeltaTime) override;
	void OnImGuiRender() override;
	void OnEvent(Sampo::Event& anEvent) override;

private:
	Sampo::ShaderLibrary m_ShaderLibrary;
	Sampo::OrthographicCameraController m_CameraController;

	std::shared_ptr<Sampo::Shader> m_SquareShader;
	std::shared_ptr<Sampo::VertexArray> m_SquareVA;

	std::shared_ptr<Sampo::Texture2D> m_Texture;
	std::shared_ptr<Sampo::Texture2D> m_TransparentTexture;

	glm::vec3 m_SquareColor{ 0.25f, 0.35f, 0.75f };
};
#pragma once
#include "sampo.hpp"

class Renderer2DLayer : public Sampo::Layer
{
public:
	Renderer2DLayer(const glm::vec2& aWindowSize = { 1280.0f, 720.0f });
	virtual ~Renderer2DLayer() = default;

	void OnAttach() override;
	void OnUpdate(Sampo::Timestep aDeltaTime) override;
	void OnImGuiRender() override;
	void OnEvent(Sampo::Event& anEvent) override;

private:
	Sampo::OrthographicCameraController m_CameraController;

	glm::vec4 m_SquareColor{ 0.25f, 0.35f, 0.75f, 1.0f };
};
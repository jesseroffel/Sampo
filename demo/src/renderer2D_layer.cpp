#include "renderer2D_layer.hpp"

#include <imgui.h>

#include <glm/gtc/type_ptr.hpp>

Renderer2DLayer::Renderer2DLayer(const glm::vec2& aWindowSize)
	: Sampo::Layer("Render2D Test Layer")
	, m_CameraController(aWindowSize.x / aWindowSize.y)
{
}

void Renderer2DLayer::OnAttach()
{
	m_Texture = Sampo::Texture2D::Create("../../../../../demo/data/assets/textures/checkerboard.png");
}

void Renderer2DLayer::OnUpdate(Sampo::Timestep aDeltaTime)
{
	m_CameraController.OnUpdate(aDeltaTime);

	Sampo::RenderCommand::Clear();

	Sampo::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Sampo::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.75f, 0.75f }, { 0.75f, 0.25f, 0.40f, 1.0f });
	Sampo::Renderer2D::DrawQuad({ 0.5f, 0.5f }, { 0.5f, 0.75f }, { 0.25f, 0.75f, 0.40f, 1.0f });
	Sampo::Renderer2D::DrawQuad({ -10.0f, -10.0f, -0.2f }, { 20.0f, 20.0f }, m_Texture, { 0.5f,0.5f,0.5f,0.5f }, 10.0f);
	Sampo::Renderer2D::DrawQuad({ -0.5f, -0.5f }, { 2.0f, 2.0f }, m_Texture, { 0.5f,0.5f,0.5f,0.5f }, 20.0f);
	//Sampo::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, -0.1f }, { 1.5f, 1.5f }, glm::radians(45.0f), {0.2f,0.2f,0.5f,1.0f});
	Sampo::Renderer2D::EndScene();
}

void Renderer2DLayer::OnImGuiRender()
{
	ImGui::Begin("DemoSettings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Renderer2DLayer::OnEvent(Sampo::Event& anEvent)
{
	m_CameraController.OnEvent(anEvent);
}

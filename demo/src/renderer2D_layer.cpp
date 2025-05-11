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

	m_squareRotation += aDeltaTime * 45.0f;
	if (m_squareRotation > 360.0f)
		m_squareRotation = m_squareRotation - 360;
	else if (m_squareRotation < -360.0f)
		m_squareRotation = m_squareRotation + 360;

	Sampo::Renderer2D::ResetStats();
	Sampo::RenderCommand::Clear();

	Sampo::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Sampo::Renderer2D::DrawQuad({ -0.50f, -0.25f }, { 0.25f, 0.20f }, { 0.75f, 0.25f, 0.40f, 1.0f });
	Sampo::Renderer2D::DrawQuad({ 0.5f, 0.25f }, { 0.35f, 0.4f }, { 0.25f, 0.75f, 0.40f, 1.0f });
	Sampo::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.2f }, { 20.0f, 20.0f }, m_Texture, { 0.5f,0.5f,0.5f,0.75f }, 10.0f);
	Sampo::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, -0.1f }, { 0.5f, 0.5f }, glm::radians(m_squareRotation), m_Texture, { 0.5f, 0.5f, 0.5f, 0.75f }, 2.5f);
	Sampo::Renderer2D::DrawRotatedQuad({ -0.0f, 0.0f, -0.1f }, { 1.5f, 1.5f }, glm::radians(-m_squareRotation), m_SquareColor);
	Sampo::Renderer2D::EndScene();

	Sampo::Renderer2D::BeginScene(m_CameraController.GetCamera());
	for (float y = -4.5f; y < 5.0f; y += 0.5f)
	{
		for (float x = -4.5f; x < 5.0f; x += 0.5f)
		{
			glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.75f };
			Sampo::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
		}
	}
	Sampo::Renderer2D::EndScene();

}

void Renderer2DLayer::OnImGuiRender()
{
	ImGui::Begin("DemoSettings");

	const Sampo::Renderer2D::Statistics& renderStatistics = Sampo::Renderer2D::GetStatistics();

	ImGui::Text("Renderer2D Statistics:");
	ImGui::Text("Draw Calls: %d", renderStatistics.m_DrawCalls);
	ImGui::Text("Quads: %d", renderStatistics.m_QuadCount);
	ImGui::Text("Vertices: %d", renderStatistics.GetTotalVertexCount());
	ImGui::Text("Indices: %d", renderStatistics.GetTotalIndicesCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::DragFloat("Rotation", &m_squareRotation);
	ImGui::End();
}

void Renderer2DLayer::OnEvent(Sampo::Event& anEvent)
{
	m_CameraController.OnEvent(anEvent);
}

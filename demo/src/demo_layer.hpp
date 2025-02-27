#pragma once
#include "sampo.hpp"

namespace Sampo
{
	class Keyboard;
}

class DemoLayer : public Sampo::Layer
{
public:
	DemoLayer();
	~DemoLayer() = default;

	void OnAttach() override;
	void OnUpdate(Sampo::Timestep aDeltaTime) override;
	void OnImGuiRender() override;

private:
	Sampo::OrthographicCamera m_Camera;

	std::shared_ptr<Sampo::Shader> m_SquareShader;
	std::shared_ptr<Sampo::VertexArray> m_SquareVA;

	std::shared_ptr<Sampo::Shader> m_TextureShader;
	std::shared_ptr<Sampo::Texture2D> m_Texture;
	std::shared_ptr<Sampo::Texture2D> m_TransparentTexture;

	const Sampo::Keyboard* m_Keyboard;

	glm::vec3 m_SquareColor{ 0.25f, 0.35f, 0.75f };
	glm::vec3 m_CameraPosition{ 0.0f };
	float m_CameraRotation{ 0.0f };
	float m_CameraMoveSpeed{ 1.0f };
	float m_CameraRotationSpeed{ 60.0f };
};
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

private:
	Sampo::OrthographicCamera m_Camera;

	std::shared_ptr<Sampo::Shader> m_Shader;
	std::shared_ptr<Sampo::VertexArray> m_VertexArray;

	std::shared_ptr<Sampo::Shader> m_SquareShader;
	std::shared_ptr<Sampo::VertexArray> m_SquareVA;

	const Sampo::Keyboard* m_Keyboard;

	glm::vec3 m_CameraPosition{ 0.0f };
	float m_CameraRotation{ 0.0f };
	float m_CameraMoveSpeed{ 1.0f };
	float m_CameraRotationSpeed{ 60.0f };
};
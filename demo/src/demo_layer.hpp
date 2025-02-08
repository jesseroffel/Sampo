#pragma once

#include "sampo.hpp"
#include "sampo/events/key_event.hpp"

namespace Sampo
{
	class Event;
	class Keyboard;
	class Shader;
	class VertexArray;
}

class DemoLayer : public Sampo::Layer
{
public:
	DemoLayer();
	~DemoLayer() = default;

	void OnAttach() override;
	void OnUpdate(float aTimeStamp) override;

private:
	bool OnKeyPressedEvent(Sampo::KeyPressedEvent& anEvent);

	Sampo::OrthographicCamera m_Camera;

	std::shared_ptr<Sampo::Shader> m_Shader;
	std::shared_ptr<Sampo::VertexArray> m_VertexArray;

	std::shared_ptr<Sampo::Shader> m_SquareShader;
	std::shared_ptr<Sampo::VertexArray> m_SquareVA;

	const Sampo::Keyboard* m_Keyboard;

	glm::vec3 m_CameraPosition;
	float m_CameraRotation;
	float m_CameraMoveSpeed;
	float m_CameraRotationSpeed;
};
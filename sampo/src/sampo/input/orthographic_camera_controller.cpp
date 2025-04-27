#include "sampo_pch.hpp"
#include "orthographic_camera_controller.hpp"

#include "sampo/core/application.hpp"
#include "keyboard.hpp"
#include "input.hpp"

namespace Sampo
{
	OrthographicCameraController::OrthographicCameraController(float anAspectRatio, bool aRotation)
		: m_AspectRatio(anAspectRatio)
		, m_Camera(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom)
		, m_Rotation(aRotation)
	{
		Sampo::Input& input = Sampo::Application::GetInstance().GetPlatform()->GetInput();
		if (const unsigned int index = input.GetFirstInputDeviceIndexByType(Sampo::InputType::kKeyboard) != -1)
			m_Keyboard = static_cast<const Sampo::Keyboard*>(input.GetInputDevice(index));
	}

	void OrthographicCameraController::OnUpdate(Timestep aTimeStep)
	{
		if (m_Keyboard->GetIsButtonPressed(KeyboardButton::kA))
			m_CameraPosition.x -= m_CameraTranslationSpeed * aTimeStep;
		if (m_Keyboard->GetIsButtonPressed(KeyboardButton::kD))
			m_CameraPosition.x += m_CameraTranslationSpeed * aTimeStep;
		if (m_Keyboard->GetIsButtonPressed(KeyboardButton::kS))
			m_CameraPosition.y -= m_CameraTranslationSpeed * aTimeStep;
		if (m_Keyboard->GetIsButtonPressed(KeyboardButton::kW))
			m_CameraPosition.y += m_CameraTranslationSpeed * aTimeStep;

		if (m_Rotation)
		{
			if (m_Keyboard->GetIsButtonPressed(KeyboardButton::kQ))
				m_CameraRotation += m_CameraRotationSpeed * aTimeStep;
			if (m_Keyboard->GetIsButtonPressed(KeyboardButton::kE))
				m_CameraRotation -= m_CameraRotationSpeed * aTimeStep;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_Zoom;
	}

	void OrthographicCameraController::OnEvent(Event& anEvent)
	{
		EventDispatcher dispatcher(anEvent);
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled, this));
		dispatcher.Dispatch<WindowsResizeEvent>(BIND_EVENT_FN(OrthographicCameraController::OnWindowResized, this));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& anEvent)
	{
		m_Zoom -= anEvent.GetOffset().y * 0.25f;
		m_Zoom = std::max(m_Zoom, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowsResizeEvent& anEvent)
	{
		m_AspectRatio = static_cast<float>(anEvent.GetWidth()) / static_cast<float>(anEvent.GetHeight());
		m_Camera.SetProjection(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom);
		return false;
	}
}

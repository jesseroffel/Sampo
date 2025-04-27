#pragma once

#include "sampo/core/timestep.hpp"
#include "sampo/events/application_event.hpp"
#include "sampo/events/mouse_event.hpp"
#include "sampo/graphics/camera.hpp"

namespace Sampo
{
	class Keyboard;

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float anAspectRatio, bool aRotation = false);

		void OnUpdate(Timestep aTimeStep);
		void OnEvent(Event& anEvent);

		const OrthographicCamera& GetCamera() { return m_Camera; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& anEvent);
		bool OnWindowResized(WindowsResizeEvent& anEvent);

		glm::vec3 m_CameraPosition{ 0.0f };

		const Keyboard* m_Keyboard{ nullptr };

		float m_AspectRatio{ -1.0f };
		float m_Zoom{ 1.0f };
		float m_CameraTranslationSpeed{ 1.0f };
		float m_CameraRotation{ 0.0f };
		float m_CameraRotationSpeed{ 60.0f };
		OrthographicCamera m_Camera;

		bool m_Rotation{ false };
	};
}
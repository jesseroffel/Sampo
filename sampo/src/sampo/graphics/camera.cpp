#include "sampo_pch.hpp"
#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace Sampo
{
	OrthographicCamera::OrthographicCamera(float aLeft, float aRight, float aBottom, float aTop)
		: m_ProjectionMatrix(glm::ortho(aLeft, aRight, aBottom, aTop, -1.0f, 1.0f))
		, m_ViewMatrix(1.0f)
		, m_Position(0.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::SetProjection(float aLeft, float aRight, float aBottom, float aTop)
	{
		m_ProjectionMatrix = glm::ortho(aLeft, aRight, aBottom, aTop, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::SetPosition(const glm::vec3& aPosition)
	{
		m_Position = aPosition;
		RecalculateViewMatrix();
	}

	void OrthographicCamera::SetRotation(float aRotation)
	{
		m_Rotation = aRotation;
		RecalculateViewMatrix();
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		const glm::mat4 identity = glm::identity<glm::mat4>();
		const float radianRotation = glm::radians(m_Rotation);
		const glm::vec3 zAxis = glm::vec3(0, 0, 1);
		const glm::mat4 transform = glm::translate(identity, m_Position) * glm::rotate(identity, radianRotation, zAxis);

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}
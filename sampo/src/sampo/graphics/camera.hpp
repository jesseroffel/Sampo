#pragma once

#include <glm/glm.hpp>

namespace Sampo
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float aLeft, float aRight, float aBottom, float aTop);

		void SetProjection(float aLeft, float aRight, float aBottom, float aTop);

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& aPosition);

		float GetRotiation() const{ return m_Rotation; }
		void SetRotation(float aRotation);


		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position;
		float m_Rotation{ 0.0f };
	};
}
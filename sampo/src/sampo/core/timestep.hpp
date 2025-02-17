#pragma once

namespace Sampo
{
	class Timestep
	{
	public:
		Timestep(float aTime = 0.0f)
			: m_Time(aTime)
		{ }

		operator float() const { return m_Time; }

		float GetSeconds() const { return m_Time; }
		float GetMilliSeconds() const { return m_Time * 1000.0f; }
	private:
		float m_Time{ 0.0f };
	};
}
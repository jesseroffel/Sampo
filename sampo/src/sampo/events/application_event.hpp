#pragma once
#include "event.hpp"

namespace Sampo
{
	class WindowsResizeEvent : public Event
	{
	public:
		WindowsResizeEvent(uint32 aWidth, uint32 aHeight) : m_Width(aWidth), m_Height(aHeight) {}

		uint32 GetWidth() const { return m_Width; }
		uint32 GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResize Event: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventApplicaton)
	private:
		uint32 m_Width, m_Height;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventApplicaton)
	};
}
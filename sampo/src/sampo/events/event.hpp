#pragma once
#include <functional>

namespace Sampo
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
		JoystickConnected, JoystickDisconnected
	};

	enum EventCategory
	{
		None = 0,
		EventInput = 1 << 0,
		EventKeyboard = 1 << 1,
		EventMouse = 1 << 2,
		EventGamepad = 1 << 3,
		EventApplicaton = 1 << 4
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class Event
	{
	public:
		virtual ~Event() = default;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		bool IsInCategory(EventCategory aCategory) { return GetCategoryFlags() & aCategory; }

		bool m_Processed = false;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& anEvent) : m_Event(anEvent) {}

		template<typename T, typename F>
		bool Dispatch(std::function<bool(T&)> aFunc)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Processed |= aFunc(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}
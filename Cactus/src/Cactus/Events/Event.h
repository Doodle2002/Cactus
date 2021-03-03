#pragma once

#include "Cactus/Core.h"

namespace Cactus
{

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowFocusLost, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCatagory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type;}\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(catagory) virtual int GetCatagoryFlags() const override { return catagory; }

	class Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCatagoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCatagory(EventCatagory catagory)
		{
			return GetCatagoryFlags() & catagory;
		}
	public:
		bool handled = false;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: event(event)
		{
		}

		template <typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (event.GetEventType() == T::GetStaticType())
			{
				event.handled = func(static_cast<T&>(event));
				return true;
			}
			return false;
		}

	private:
		Event& event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}
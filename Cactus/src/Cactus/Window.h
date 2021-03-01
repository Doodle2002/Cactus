#pragma once


#include "cactus_pch.h"

#include "Cactus/Core.h"
#include "Cactus/Events/Event.h"

#include "Cactus/Events/ApplicationEvent.h"

namespace Cactus
{
	struct WindowProps
	{
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProps(const std::string& title = "Cactus Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: title(title), width(width), height(height)
		{
		}
	};

	//Interace for all different kinds of windows
	class CACTUS_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {};
		virtual void OnUpdate() = 0;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;
		static Window* Create(const WindowProps& props = WindowProps());
	};
}
#pragma once


#include "cactus_pch.h"

#include "Cactus/Core/Core.h"
#include "Cactus/Events/Event.h"

#include "Cactus/Events/ApplicationEvent.h"

namespace Cactus
{
	struct WindowProps
	{
		std::string title;
		uint32_t width;
		uint32_t height;

		WindowProps(const std::string& title = "Cactus App",
			uint32_t width = 1280,
			uint32_t height = 720)
			: title(title), width(width), height(height)
		{
		}
	};

	//Interace for all different kinds of windows
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {};
		virtual void OnUpdate() = 0;
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;
		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};
}

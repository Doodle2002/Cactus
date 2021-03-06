#pragma once

#include "Cactus/Core/Window.h"
#include "Cactus/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Cactus {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		unsigned int GetWidth() const override { return data.width; }
		unsigned int GetHeight() const override { return data.height; }

		// Window attributes
		void SetEventCallback(const EventCallbackFn& callback) override { data.eventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* window;

		GraphicsContext* context;
		struct WindowData
		{
			std::string title;
			unsigned int width, height;
			bool vSync;

			EventCallbackFn eventCallback;
		};

		WindowData data;
	};

}
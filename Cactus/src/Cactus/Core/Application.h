#pragma once

#include "Cactus/Core/Core.h"

#include "Cactus/Core/Window.h"
#include "Cactus/Core/LayerStack.h"
#include "Cactus/Events/Event.h"
#include "Cactus/Events/ApplicationEvent.h"
#include "Cactus/ImGui/ImGuiLayer.h"
#include "Cactus/Core/Timestep.h"

namespace Cactus {
	class Time;

	class Application
	{
		friend class Time;
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline bool IsMinimized() { return minimized; }

		inline static Application& Get() { return *instance; }
		inline Window& GetWindow() { return *window; }
		
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		void InternalTimeUpdate();

	private:

		Scope<Window> window;
		ImGuiLayer* imGuiLayer;

		bool running = false;
		bool minimized = false;
		LayerStack layerStack;
		float lastTime = 0.0f;
	private:

		static Application* instance;

		//friend void Time::SetDeltaTime(float delta);
	};

	//Client defined
	Application* CreateApplication();

}

//#include "Cactus/Core/Time.h"
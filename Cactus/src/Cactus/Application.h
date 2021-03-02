#pragma once

#include "Cactus/Core.h"

#include "Cactus/Window.h"
#include "Cactus/LayerStack.h"
#include "Cactus/Events/Event.h"
#include "Cactus/Events/ApplicationEvent.h"
#include "Cactus/ImGui/ImGuiLayer.h"
#include "Cactus/Core/Timestep.h"

namespace Cactus {
	class Time;

	class CACTUS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *instance; }
		inline Window& GetWindow() { return *window; }
		void InternalTimeUpdate();
	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:

		std::unique_ptr<Window> window;
		ImGuiLayer* imGuiLayer;

		bool running = false;
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
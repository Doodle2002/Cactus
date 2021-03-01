#pragma once

#include "Cactus/Core.h"

#include "Cactus/Window.h"
#include "Cactus/LayerStack.h"
#include "Cactus/Events/Event.h"
#include "Cactus/Events/ApplicationEvent.h"

#include "Cactus/ImGui/ImGuiLayer.h"

namespace Cactus {
	class CACTUS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *instance;  }
		inline Window& GetWindow() { return *window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		
		std::unique_ptr<Window> window;
		ImGuiLayer* imGuiLayer;

		bool running = false;
		LayerStack layerStack;

		static Application* instance;
	};

	//Client defined
	Application* CreateApplication();

}
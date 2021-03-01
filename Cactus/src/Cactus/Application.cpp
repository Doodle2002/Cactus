#include "cactus_pch.h"

#include "Cactus/Application.h"
#include "Cactus/Log.h"
#include "Cactus/Input.h"

#include "glm/glm.hpp"
namespace Cactus {

	#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::instance = nullptr;

	Application::Application()
	{

		CACTUS_CORE_ASSERT(!instance, "Application instance already exists!");
		instance = this;
		window = std::unique_ptr<Window>(Window::Create());
		window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		imGuiLayer = new ImGuiLayer();
		PushOverlay(imGuiLayer);
	}
	Application::~Application()
	{
	}


	void Application::PushLayer(Layer* layer)
	{
		layerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		layerStack.PushOverlay(layer);
	}


	void Application::OnEvent(Event& e) 
	{
		//CACTUS_CORE_TRACE(e);

		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = layerStack.end(); it != layerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.handled)
			{
				break;
			}
		}
	}

	

	void Application::Run()
	{
		if (running)
		{
			return;
		}
		running = true;
		while (running) 
		{
			
			for (Layer* layer : layerStack)
			{
				layer->OnUpdate();
			}

			imGuiLayer->Begin();
			for (Layer* layer : layerStack)
			{
				layer->OnImGuiRender();
			}
			imGuiLayer->End();
			window->OnUpdate();
		}

	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		running = false;
		return true;
	}
}
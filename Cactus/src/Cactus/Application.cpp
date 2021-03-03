#include "cactus_pch.h"

#include "Cactus/Application.h"
#include "Cactus/Log.h"
#include "Cactus/Input.h"
#include "Cactus/Renderer/Renderer.h"

#include "glm/glm.hpp"

//#include <glfw/glfw3.h>

#include "Cactus/Core/Time.h"

namespace Cactus {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::instance = nullptr;


	Application::Application()
	{

		CACTUS_CORE_ASSERT(!instance, "Application instance already exists!");
		instance = this;
		window = std::unique_ptr<Window>(Window::Create());
		window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();
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
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

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


			InternalTimeUpdate();
			//Time::SetDeltaTime(time - lastTime);
			//float delta = time - lastTime;

			Input::Update();

			
			for (Layer* layer : layerStack)
			{
				layer->OnUpdate();
			}

			if (!minimized)
			{
				for (Layer* layer : layerStack)
				{
					layer->OnRender();
				}
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

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			minimized = true;
			return false;
		}

		minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}

	void Application::InternalTimeUpdate()
	{
		Time::Update();
	}
}
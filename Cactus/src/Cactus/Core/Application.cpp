#include "cactus_pch.h"

#include "Application.h"
#include "Cactus/Core/Log.h"
#include "Cactus/Core/Input.h"
#include "Cactus/Renderer/Renderer.h"

#include "glm/glm.hpp"

//#include <glfw/glfw3.h>

#include <glad/glad.h>
#include "Cactus/Core/Time.h"

namespace Cactus {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::instance = nullptr;


	Application::Application()
	{
		CACTUS_PROFILE_FUNCTION();

		CACTUS_CORE_ASSERT(!instance, "Application instance already exists!");
		instance = this;
		window = Window::Create();
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
		CACTUS_PROFILE_FUNCTION();
		if (running)
		{
			return;
		}

		running = true;


		while (running)
		{
			CACTUS_PROFILE_SCOPE("while(running) - Application::Run");

			glEnable(GL_BLEND);

			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			

			InternalTimeUpdate();

			Input::Update();

			{
				CACTUS_PROFILE_SCOPE("Application -> Layer::OnUpdate");
				for (Layer* layer : layerStack)
					layer->OnUpdate();
			}
			

			if (!minimized)
			{
				CACTUS_PROFILE_SCOPE("Application -> Layer::OnRender");
				for (Layer* layer : layerStack)
					layer->OnRender();
			}


			imGuiLayer->Begin();
			{
				CACTUS_PROFILE_SCOPE("Application -> Layer::OnImGuiRender");
				for (Layer* layer : layerStack)
				{
					layer->OnImGuiRender();
				}
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
		
		//TODO: Move this to renderer class (and check if option 'maintain aspect' is true)

		//THIS ACTUALL WORKS (but is turned off because it might mess up the 2d camera)
		/*
		float preferredRatio = 1280.0f / 720.0f;

		float width = e.GetWidth();
		float height = e.GetHeight();

		float ratio = (float)e.GetWidth() / (float)e.GetHeight();
		if (e.GetWidth() / e.GetHeight() < 16.0f / 9.0f)
		{
			height = e.GetWidth() * (1.0f / preferredRatio);
		}
		else
		{
			width = e.GetHeight() * preferredRatio;
		}

		RenderCommand::SetViewport(width, 0, width, height);
		*/

		Renderer::OnWindowResize(e.GetWidth(),e.GetHeight());
		return false;
	}

	void Application::InternalTimeUpdate()
	{
		Time::Update();
	}
}
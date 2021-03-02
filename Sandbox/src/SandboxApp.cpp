#include <Cactus.h>

#include "imgui/imgui.h"

class ExampleLayer : public Cactus::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		/*
		int key = CACTUS_KEY_F;
		bool pressed = Cactus::Input::KeyPressed(key);
		if (Cactus::Input::KeyDown(key) && !pressed)
		{
			CACTUS_INFO("F Down");
		}

		if (pressed)
		{
			CACTUS_INFO("F Pressed");
		}

		if(Cactus::Input::KeyReleased(key))
		{
			CACTUS_INFO("F Released");
		}
		*/
	}

	void OnImGuiRender()
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello world!");
		ImGui::End();
	}

	void OnEvent(Cactus::Event& event) override
	{
		//CACTUS_TRACE("{0}",event);
	}

};

class Sandbox : public Cactus::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		//PushOverlay(new Cactus::InputLayer());
	}

	~Sandbox()
	{
	}
};

Cactus::Application* Cactus::CreateApplication() {
	return new Sandbox();
}
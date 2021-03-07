#include <Cactus.h>
#include <Cactus/Core/EntryPoint.h>

#include "Sandbox2D.h"


class Sandbox : public Cactus::Application
{
public:
	Sandbox()
	{
		PushLayer(new Sandbox2D());
		//PushOverlay(new Cactus::DebugLayer());
	}

	~Sandbox()
	{
	}
};

Cactus::Application* Cactus::CreateApplication() {
	return new Sandbox();
}
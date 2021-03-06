#pragma once


#ifdef CACTUS_PLATFORM_WINDOWS

extern Cactus::Application* Cactus::CreateApplication();

int main(int argc, char** argv)
{
	Cactus::Log::Init();

	CACTUS_PROFILE_BEGIN_SESSION("Startup", "CactusProfile-Startup.json");
	auto app = Cactus::CreateApplication();
	CACTUS_PROFILE_END_SESSION();


	CACTUS_PROFILE_BEGIN_SESSION("Runtime", "CactusProfile-Runtime.json");
	app->Run();
	CACTUS_PROFILE_END_SESSION();


	CACTUS_PROFILE_BEGIN_SESSION("Shutdown", "CactusProfile-Shutdown.json");
	delete app;
	CACTUS_PROFILE_END_SESSION();
}

#endif

#include "cactus_pch.h"

#include "DebugLayer.h"

#include <imgui.h>
#include "Cactus/Core/Application.h"
#include "Cactus/Debug/Instrumentor.h"

namespace Cactus {

	DebugLayer::DebugLayer()
		: Layer("Debug")
	{

	}
	void DebugLayer::OnImGuiRender()
	{
		//bool show = true;
		//ImGui::ShowDemoWindow(&show);

		bool applicationVSync = Application::Get().GetWindow().IsVSync();
		bool enableVSync = applicationVSync;

		ImGui::Begin("Debug");
		
		/*if (ImGui::CollapsingHeader("Time"))
		{
			ImGui::Text(("Time since start: " + std::to_string(Time::GetTime())).c_str());
			ImGui::Text(("Delta time:       " + std::to_string(Time::GetDeltaTime())).c_str());
			ImGui::Text(("FPS:              " + std::to_string(1.0f / Time::GetDeltaTime())).c_str());
		}
		*/
		/*
		if (!Instrumentor::Get().IsActive())
		{
			if (ImGui::Button("Start profiling"))
			{
				CACTUS_PROFILE_BEGIN_SESSION("Runtime Fragment", "CactusProfile-Runtime-Fragment.json");
			}
		}
		else {
			if (ImGui::Button("Stop"))
			{
				CACTUS_PROFILE_END_SESSION();
			}
		}
		*/

		if (ImGui::CollapsingHeader("Rendering"))
		{
			ImGui::Checkbox("Enable VSync", &enableVSync);
		}


		if (enableVSync != applicationVSync)
		{
			Application::Get().GetWindow().SetVSync(enableVSync);
		}

		ImGui::End();
	}
}
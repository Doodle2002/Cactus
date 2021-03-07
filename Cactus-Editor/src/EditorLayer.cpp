#include "EditorLayer.h"

#include <imgui/imgui.h>
#include <glm\glm\gtc\type_ptr.hpp>

#include <glm\glm\gtc\matrix_transform.hpp>

namespace Cactus {
	EditorLayer::EditorLayer()
		: Layer("Sandbox2D"), cameraController(1280.0f / 720.0f)
	{
		//particleSystem = CreateRef<ParticleSystem>();
		texture = Texture2D::Create("assets/textures/Sandstone 16x16.png");
		FramebufferData fbData;

		fbData.width = 1280;
		fbData.height = 720;

		framebuffer = Framebuffer::Create(fbData);


		cameraController.SetAutoResize(false);
	}
	void EditorLayer::OnAttach()
	{
	
	}
	void EditorLayer::OnDetach()
	{

	}
	void EditorLayer::OnUpdate()
	{
		CACTUS_PROFILE_FUNCTION();
		cameraController.OnUpdate();
	}
	void EditorLayer::OnRender()
	{
		CACTUS_PROFILE_FUNCTION();
	
		Renderer2D::ResetStats();

		framebuffer->Bind();
		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RenderCommand::Clear();

		Renderer2D::BeginScene(cameraController.GetCamera());
	
		Ref<SubTexture2D> sub = SubTexture2D::CreateFromCoords(texture, { 0.0f,0.0f }, { 16.0f,16.0f });
		for (float y = 0; y < (float)height; y ++)
		{
			for (float x = 0; x < (float)width; x ++)
			{
				glm::vec4 color = { x / (float)width, 0.5f,  y / (float)height,1.0f };
				Renderer2D::DrawQuad({x * (0.25f+spread),y*(0.25f+spread),0.2f }, {0.25f, 0.25f }, sub, color);
			}
		}
	
	
		Renderer2D::EndScene();
		framebuffer->Unbind();
	}
	void EditorLayer::OnImGuiRender()
	{
		CACTUS_PROFILE_FUNCTION();
	

		//ImGui::ShowDemoWindow();
		static bool dockspaceOpen = true;
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->GetWorkPos());
			ImGui::SetNextWindowSize(viewport->GetWorkSize());
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows,
				// which we can't undo at the moment without finer window depth/z control.

				if (ImGui::MenuItem("Exit"))
					Application::Get().Close();
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0,0 });
		ImGui::Begin("Viewport");
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

		if (viewportSize.x != viewportPanelSize.x || viewportSize.y != viewportPanelSize.y)
		{
			framebuffer->Resize((uint32_t) viewportPanelSize.x,(uint32_t) viewportPanelSize.y);
			viewportSize = { viewportPanelSize.x,viewportPanelSize.y };
			cameraController.Resize(viewportPanelSize.x, viewportPanelSize.y);
		}

		/*ImGui::Text(("Draw calls: " + std::to_string(Renderer2D::GetStats().drawCalls)).c_str());
		ImGui::ColorEdit4("Color", glm::value_ptr(color));
		ImGui::SliderInt("Width", &width, 1, 250);
		ImGui::SliderInt("Height", &height, 1, 250);
		ImGui::SliderFloat("Spread", &spread, 0.0f, 2.0f);
		*/
		uint32_t textureID = framebuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, viewportPanelSize, { 0,1 }, { 1,0 });
		//ImGui::Image((void*)textureID, { 1280,760 }, { 0, 1 }, { 1,0 });
		ImGui::End();

		ImGui::PopStyleVar();
		ImGui::End();

	}
	void EditorLayer::OnEvent(Event& e)
	{
		cameraController.OnEvent(e);
	}

}

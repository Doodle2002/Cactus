#include "Sandbox2D.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include "imgui/imgui.h"
#include <glm\glm\gtc\type_ptr.hpp>

#include <glm\glm\gtc\matrix_transform.hpp>
Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), cameraController(1280.0f / 720.0f)
{
	particleSystem = Cactus::CreateRef<ParticleSystem>();
	texture = Cactus::Texture2D::Create("assets/textures/Sandstone 16x16.png");
    Cactus::FramebufferData fbData;

    fbData.width = 1280;
    fbData.height = 720;

    framebuffer = Cactus::Framebuffer::Create(fbData);
}
void Sandbox2D::OnAttach()
{
	
}
void Sandbox2D::OnDetach()
{

}
void Sandbox2D::OnUpdate()
{
	CACTUS_PROFILE_FUNCTION();
	cameraController.OnUpdate();
	
	/*particleSystem->OnUpdate();
	internalTimer += Cactus::Time::GetDeltaTime();

	if (internalTimer > 0.1f)
	{
		ParticleData particle;
		particle.position = { 0.0f,0.0f };
		particle.velocity = { 0.3f,0.5f };
		particle.color = { 1.0f,1.0f,1.0f,1.0f };
		particle.endColor = { 1.0f,0.0f,0.0f,0.0f };
		particle.rotation = 0;
		particle.rotationSpeed = 90.0f;
		particle.size = { 0.1f,0.1f };
		particle.endSize = { 0.3f, 0.3f };
		particle.lifeTime = 2.0f;

		particleSystem->Emit(particle);
		internalTimer = 0.0f;
	}*/



}
void Sandbox2D::OnRender()
{
	CACTUS_PROFILE_FUNCTION();
	
	Cactus::Renderer2D::ResetStats();

    //framebuffer->Bind();
	Cactus::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Cactus::RenderCommand::Clear();

	Cactus::Renderer2D::BeginScene(cameraController.GetCamera());
	
	Cactus::Ref<Cactus::SubTexture2D> sub = Cactus::SubTexture2D::CreateFromCoords(texture, { 0.0f,0.0f }, { 16.0f,16.0f });
	for (float y = 0; y < (float)height; y ++)
	{
		for (float x = 0; x < (float)width; x ++)
		{
			glm::vec4 color = { x / (float)width, 0.5f,  y / (float)height,1.0f };
			Cactus::Renderer2D::DrawQuad({x * (0.25f+spread),y*(0.25f+spread),0.2f }, {0.25f, 0.25f }, sub, color);
		}
	}
	
	Cactus::Renderer2D::EndScene();
    //framebuffer->Unbind();
	//Cactus::Renderer2D::BeginScene(cameraController.GetCamera());
	//particleSystem->OnRender();
	//Cactus::Renderer2D::EndScene();
}
void Sandbox2D::OnImGuiRender()
{
	CACTUS_PROFILE_FUNCTION();
	

	


    ImGui::Begin("Render test");
    ImGui::Text(("Draw calls: " + std::to_string(Cactus::Renderer2D::GetStats().drawCalls)).c_str());
    ImGui::ColorEdit4("Color", glm::value_ptr(color));
    ImGui::SliderInt("Width", &width, 1, 250);
    ImGui::SliderInt("Height", &height, 1, 250);
    ImGui::SliderFloat("Spread", &spread, 0.0f, 2.0f);

    uint32_t textureID = framebuffer->GetColorAttachmentRendererID();
    ImGui::Image((void*)textureID, ImVec2{ 1280.0f, 720.0f }, { 0.0f,1.0f }, { 1.0f,0.0f });
    ImGui::End();

}
void Sandbox2D::OnEvent(Cactus::Event& e)
{
	cameraController.OnEvent(e);
}

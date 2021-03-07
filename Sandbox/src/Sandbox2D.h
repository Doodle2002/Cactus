#pragma once

#include "Cactus.h"
#include "ParticleSystem.h"


class Sandbox2D : public Cactus::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate() override;
	virtual void OnRender() override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Cactus::Event& e) override;
private:
	//Temp
	Cactus::Ref<Cactus::VertexArray> vertexArray;
	Cactus::Ref<Cactus::Shader> shader;
	Cactus::OrthographicCameraController cameraController;
	Cactus::Ref<Cactus::Texture2D> texture;
	Cactus::Ref<Cactus::Framebuffer> framebuffer;
	//Cactus::Ref<Cactus::SubTexture2D> texture;

	glm::vec4 color = glm::vec4(1.0f,0.0f,0.0f,1.0f);

	int width = 1;
	int height = 1;
	float spread = 0.1f;

	Cactus::Ref<ParticleSystem> particleSystem;

	float internalTimer = 0.0f;
};
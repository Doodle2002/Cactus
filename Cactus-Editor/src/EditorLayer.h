#pragma once

#include "Cactus.h"

#include <imgui/imgui.h>

namespace Cactus {
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnRender() override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;
	private:
		//Temp
		Ref<VertexArray> vertexArray;
		Ref<Shader> shader;
		OrthographicCameraController cameraController;
		Ref<Texture2D> texture;
		Ref<Framebuffer> framebuffer;
		//Ref<SubTexture2D> texture;

		glm::vec4 color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

		int width = 20;
		int height = 20;
		float spread = 0.05f;

		glm::vec2 viewportSize;
		//Ref<ParticleSystem> particleSystem;

		float internalTimer = 0.0f;
	};

}

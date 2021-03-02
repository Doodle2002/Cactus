#include "cactus_pch.h"
#include "Renderer.h"


namespace Cactus {
	
	Renderer::SceneData* Renderer::sceneData = new Renderer::SceneData;
	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		sceneData->viewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		shader->SetUniformMat4("u_ViewProjection", sceneData->viewProjectionMatrix);
		shader->SetUniformMat4("u_Transform", transform);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}

#pragma once

#include "RendererAPI.h"
namespace Cactus {

	class RenderCommand
	{
	public:

		inline static  void SetClearColor(const glm::vec4& color)
		{
			rendererAPI->SetClearColor(color);
		}
		inline static  void Clear()
		{
			rendererAPI->Clear();
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			rendererAPI->DrawIndexed(vertexArray);
		}

	private:
		static RendererAPI* rendererAPI;
	};
}
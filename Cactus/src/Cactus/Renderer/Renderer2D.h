#pragma once

#include "OrthographicCamera.h"

#include "Texture.h"
#include "SubTexture2D.h"

namespace Cactus {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void Flush();

		/////////////////////////
		//TEXTURE2D//////////////
		/////////////////////////

		//COLOR
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);

		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);

		//TEXTURE
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& color);

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec4& color);

		
		
		static void DrawQuad(const glm::mat4& transform, const Ref<Texture2D> texture, const glm::vec4& tint);


		/////////////////////////
		//SUBTEXTURE2D///////////
		/////////////////////////
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<SubTexture2D>& texture, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<SubTexture2D>& texture, const glm::vec4& color);

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<SubTexture2D>& texture, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<SubTexture2D>& texture, const glm::vec4& color);


		static void DrawQuad(const glm::mat4& transform, const Ref<SubTexture2D> texture, const glm::vec4& tint);




		//Main drawing method
		static void DrawQuad(const glm::mat4& transform, const Ref<Texture2D> texture, const glm::vec2* textureCoords, const glm::vec4& tint);

		struct Statistics
		{
			uint32_t drawCalls = 0;
			uint32_t quadCount = 0;

			uint32_t GetTotalVertexCount() { return quadCount * 4; }
			uint32_t GetTotalIndexCount() { return quadCount * 6; }
		};

		static Statistics GetStats();
		static void ResetStats();
	private:
		static void FlushAndReset();
		//static void EndBatch();
	};
}
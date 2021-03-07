#pragma once

#include "Texture.h"
#include <glm/glm.hpp>
namespace Cactus {

	class SubTexture2D
	{
	public:
		SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max);

		const Ref<Texture2D> GetTexture() const { return texture; }
		const glm::vec2* GetTexCoords() const { return texCoords; }

		static Ref<SubTexture2D> CreateFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& spriteSize);
	private:
		Ref<Texture2D> texture;
		glm::vec2 texCoords[4];
	};
}
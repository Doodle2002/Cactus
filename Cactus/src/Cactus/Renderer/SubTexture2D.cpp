#include "cactus_pch.h"


#include "SubTexture2D.h"

namespace Cactus {
	
	SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max)
		: texture(texture)
	{
		texCoords[0] = { min.x,min.y };
		texCoords[1] = { max.x,min.y };
		texCoords[2] = { max.x,max.y };
		texCoords[3] = { min.x,max.y };
	}


	Ref<SubTexture2D> SubTexture2D::CreateFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& spriteSize)
	{
		glm::vec2 min = { (coords.x * spriteSize.x) / texture->GetWidth(), (coords.y * spriteSize.y) / texture->GetHeight() };
		glm::vec2 max = { ((coords.x + 1) * spriteSize.x) / texture->GetWidth(), ((coords.y + 1) * spriteSize.y) / texture->GetHeight() };

		return CreateRef<SubTexture2D>(texture, min, max);
	}
}
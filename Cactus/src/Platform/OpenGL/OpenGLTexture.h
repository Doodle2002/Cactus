#pragma once

#include "Cactus/Renderer/Texture.h"

#include <glad/glad.h>
namespace Cactus {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(uint32_t width, uint32_t height);

		virtual ~OpenGLTexture2D();


		virtual uint32_t GetWidth() const override { return width; }
		virtual uint32_t GetHeight() const override { return height; }

		virtual void SetData(void* data, uint32_t size) override;

		virtual void Bind(uint32_t slot = 0) const override;

		virtual bool operator==(const Texture& other) const override
		{
			return rendererID == ((OpenGLTexture2D&) other).rendererID;
		}
	private:
		std::string path;

		uint32_t width, height;
		uint32_t rendererID;

		GLenum internalFormat, dataFormat;
	};
}
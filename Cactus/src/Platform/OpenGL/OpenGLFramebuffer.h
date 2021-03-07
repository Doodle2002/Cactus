#pragma once

#include "Cactus/Renderer/Framebuffer.h"

namespace Cactus {

	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferData& data);
		virtual ~OpenGLFramebuffer();

		void Invalidate();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual uint32_t GetColorAttachmentRendererID() const override { return colorAttachment; }
		virtual const FramebufferData& GetData() const override { return data; }

	private:
		uint32_t rendererID;
		uint32_t colorAttachment, depthAttachment;
		FramebufferData data;
	};
}

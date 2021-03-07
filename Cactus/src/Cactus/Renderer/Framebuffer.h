#pragma once

#include "Cactus/Core/Core.h"

namespace Cactus {

	struct FramebufferData
	{
		uint32_t width, height;
		uint32_t samples = 1;

		bool swapChainTarget = false;
	};

	class Framebuffer
	{
	public:
		virtual ~Framebuffer();
		virtual const FramebufferData& GetData() const = 0;

		virtual uint32_t GetColorAttachmentRendererID() const = 0;
		static Ref<Framebuffer> Create(const FramebufferData& data);

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;
	};
}

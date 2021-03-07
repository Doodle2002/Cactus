#include "cactus_pch.h"

#include "Framebuffer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"
#include "Renderer.h"

namespace Cactus {

	Ref<Framebuffer> Framebuffer::Create(const FramebufferData& data)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: CACTUS_CORE_ASSERT(false, "RendererAPI::None is not supported");  return  nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLFramebuffer>(data);
		}

		CACTUS_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
#include "cactus_pch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Cactus
{
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: CACTUS_CORE_ASSERT(false, "RendererAPI::None is not supported");  return  nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(size);
		}

		CACTUS_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;

	}
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: CACTUS_CORE_ASSERT(false, "RendererAPI::None is not supported");  return  nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(vertices,size);
		}

		CACTUS_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}






	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: CACTUS_CORE_ASSERT(false, "RendererAPI::None is not supported");  return  nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLIndexBuffer>(indices, count);
		}

		CACTUS_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
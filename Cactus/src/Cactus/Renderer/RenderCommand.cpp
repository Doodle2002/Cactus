#include "cactus_pch.h"

#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Cactus {

	RendererAPI* RenderCommand::rendererAPI = new OpenGLRendererAPI;
}
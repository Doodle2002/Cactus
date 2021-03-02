#pragma once

#include "Cactus/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Cactus
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* windowHandle;
	};
}
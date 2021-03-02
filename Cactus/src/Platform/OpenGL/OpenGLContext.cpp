#include "cactus_pch.h"

#include "OpenGLContext.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Cactus
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: windowHandle(windowHandle)
	{
		CACTUS_CORE_ASSERT(windowHandle, "Handle is null!");
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CACTUS_CORE_ASSERT(status, "Failed to initialize glad");


		CACTUS_CORE_INFO("OpenGL Info:");
		CACTUS_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR)); 
		CACTUS_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		CACTUS_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(windowHandle);
	}
}
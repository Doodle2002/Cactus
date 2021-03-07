#include "cactus_pch.h"

#include "OpenGLFramebuffer.h"
#include <glad/glad.h>
namespace Cactus {
	
	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferData& data)
		: data(data)
	{
		Invalidate();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &rendererID);
		glDeleteTextures(1, &colorAttachment);
		glDeleteTextures(1, &depthAttachment);
	}

	void OpenGLFramebuffer::Invalidate()
	{
		if (rendererID)
		{
			glDeleteFramebuffers(1, &rendererID);
			glDeleteTextures(1, &colorAttachment);
			glDeleteTextures(1, &depthAttachment);
		}

		glCreateFramebuffers(1, &rendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, rendererID);
		
		glCreateTextures(GL_TEXTURE_2D,1, &colorAttachment);
		glBindTexture(GL_TEXTURE_2D, colorAttachment);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, data.width, data.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorAttachment, 0);

		glCreateTextures(GL_TEXTURE_2D, 1, &depthAttachment);
		glBindTexture(GL_TEXTURE_2D, depthAttachment);

		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, data.width, data.height);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, data.width, data.height ,0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthAttachment, 0);

		CACTUS_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, rendererID);
		glViewport(0, 0, data.width, data.height);
	}

	void OpenGLFramebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}


	void OpenGLFramebuffer::Resize(uint32_t width, uint32_t height)
	{
		data.width = width;
		data.height = height;
		Invalidate();
	}
}

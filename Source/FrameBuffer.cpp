#include "FrameBuffer.h"
#include"glew/glew.h"
#include"Texture.h"

FrameBuffer::FrameBuffer()
{
	glGenFramebuffers(1, &m_RendererID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

	glGenTextures(1, &colorAttachment);
	glBindTexture(GL_TEXTURE_2D, colorAttachment);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 600, 600, 0, GL_RGB,
		GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
		colorAttachment, 0);

	glEnable(GL_DEPTH_TEST);
	glGenTextures(1, &depthAttachment);
	glBindTexture(GL_TEXTURE_2D, depthAttachment);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, 1000, 1000);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
		std::cout << "FrameBuffer Completed" << std::endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &m_RendererID);
	std::cout << "FrameBuffer Deleted" << std::endl;
}

void FrameBuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
}

void FrameBuffer::UnBind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned int FrameBuffer::GetRendererID()
{
	return m_RendererID;
}

unsigned int FrameBuffer::GetColorTexture()
{
	return colorAttachment;
}

unsigned int FrameBuffer::GetDepthTexture()
{
	return depthAttachment;
}
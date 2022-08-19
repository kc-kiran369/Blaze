#include "FrameBuffer.h"
#include"glew/glew.h"
#include"Texture.h"

FrameBuffer::FrameBuffer()
{
	glGenFramebuffers(1, &m_RendererID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 600, 600, 0, GL_RGB,
		GL_UNSIGNED_BYTE, nullptr);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
		texture, 0);

	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 600, 600);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
		GL_RENDERBUFFER, rbo);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &m_RendererID);
}

void FrameBuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glBindTexture(GL_TEXTURE_2D, texture);
}

void FrameBuffer::UnBind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int FrameBuffer::GetRendererID()
{
	return m_RendererID;
}

unsigned int FrameBuffer::GetTexture()
{
	return texture;
}

unsigned int FrameBuffer::GetRBO()
{
	return rbo;
}

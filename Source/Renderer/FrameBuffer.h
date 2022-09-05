#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include"glew/glew.h"
#include"Benchmark/Logger.h"

class FrameBuffer
{
private:
	unsigned int m_RendererID, colorAttachment, depthAttachment, renderBuffer;
public:
	FrameBuffer();
	~FrameBuffer();

	void Bind();
	void UnBind();

	unsigned int GetRendererID();
	unsigned int GetColorTexture();
	unsigned int GetDepthTexture();
};
#endif
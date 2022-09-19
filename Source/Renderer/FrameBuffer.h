#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include<iostream>
#include"glew/glew.h"
#include"Benchmark/Logger.h"

class FrameBuffer
{
private:
	uint32_t m_RendererID, colorAttachment, depthAttachment, renderBuffer;
public:
	FrameBuffer();
	~FrameBuffer();

	void Bind();
	void UnBind();

	uint32_t GetRendererID();
	uint32_t GetColorTexture();
	uint32_t GetDepthTexture();
};
#endif
#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

class FrameBuffer
{
private:
	unsigned int m_RendererID, colorAttachment, depthAttachment;
public:
	FrameBuffer();
	~FrameBuffer();

	void Bind();
	void UnBind();

	unsigned int GetRendererID();
	unsigned int GetTexture();
};
#endif
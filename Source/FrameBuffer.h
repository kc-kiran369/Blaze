#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

class FrameBuffer
{
private:
	unsigned int m_RendererID, texture, rbo;
public:
	FrameBuffer();
	~FrameBuffer();

	void Bind();
	void UnBind();

	unsigned int GetRendererID();
	unsigned int GetTexture();
	unsigned int GetRBO();
};

#endif
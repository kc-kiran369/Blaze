#ifndef VERTEX_BUFFER_CLASS_H
#define VERTEX_BUFFER_CLASS_H

#include "glew/glew.h"
#include "glm/glm.hpp"

class VertexBuffer
{
private:
	uint32_t m_RendererID;
public:
	VertexBuffer(uint32_t size, void* data);
	~VertexBuffer();

	void Bind();
	void UnBind();
};
#endif
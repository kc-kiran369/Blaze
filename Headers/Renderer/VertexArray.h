#ifndef VERTEX_ARRAY_CLASS_H
#define VERTEX_ARRAY_CLASS_H

#include"glew/glew.h"
#include"VertexBuffer.h"

class VertexArray
{
private:
	uint32_t m_RendererID;
public:
	VertexArray();

	void LinkAttrib(VertexBuffer& vbo, uint32_t vertexSize, uint32_t layout, float stride, void* pointer);
	void Bind();
	void UnBind();
	uint32_t GetID();
	void Delete();
};
#endif
#ifndef VERTEX_ARRAY_CLASS_H
#define VERTEX_ARRAY_CLASS_H

#include"VertexBuffer.h"
#include"glew/glew.h"

class VertexArray
{
private:
	unsigned int m_RendererID;
public:
	VertexArray();

	void LinkAttrib(VertexBuffer& vbo, unsigned int vertexSize, unsigned int layout, float stride, void* pointer);
	void Bind();
	void UnBind();
	unsigned int GetID();
	void Delete();
};
#endif
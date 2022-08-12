#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererID);
	glBindVertexArray(m_RendererID);
}

void VertexArray::LinkAttrib(VertexBuffer& vbo,unsigned int vertexSize, unsigned int layout, float stride, void* pointer)
{
	vbo.Bind();
	glVertexAttribPointer(layout, vertexSize, GL_FLOAT, GL_FALSE, stride, pointer);
	glEnableVertexAttribArray(layout);
	vbo.UnBind();
}

void VertexArray::Bind()
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::UnBind()
{
	glBindVertexArray(0);
}

unsigned int VertexArray::GetID()
{
	return m_RendererID;
}

void VertexArray::Delete()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

#include"Renderer/IndexBuffer.h"

IndexBuffer::IndexBuffer(uint32_t size, void* data)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	m_Count = size/sizeof(uint32_t);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, &m_RendererID);
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::UnBind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

uint32_t IndexBuffer::GetRendererID()
{
	return m_RendererID;
}

uint32_t IndexBuffer::GetCount()
{
	return m_Count;
}

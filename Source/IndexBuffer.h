#ifndef INDEX_BUFFER_CLASS_H
#define INDEX_BUFFER_CLASS_H

#include "glew/glew.h"

class IndexBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	IndexBuffer(unsigned int size, void* data);
	~IndexBuffer();

	void Bind();
	void UnBind();

	unsigned int GetRendererID();
	unsigned int GetCount();
};
#endif
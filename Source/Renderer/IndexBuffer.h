#ifndef INDEX_BUFFER_CLASS_H
#define INDEX_BUFFER_CLASS_H

#include "glew/glew.h"
#include<stdint.h>

class IndexBuffer
{
private:
	uint32_t m_RendererID;
	uint32_t m_Count;
public:
	IndexBuffer(uint32_t size, void* data);
	~IndexBuffer();

	void Bind();
	void UnBind();

	uint32_t GetRendererID();
	uint32_t GetCount();
};
#endif
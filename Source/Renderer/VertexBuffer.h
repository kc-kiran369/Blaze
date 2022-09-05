#ifndef VERTEX_BUFFER_CLASS_H
#define VERTEX_BUFFER_CLASS_H

#include "glew/glew.h"
#include "glm/glm.hpp"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 uv;
};

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(unsigned int size, void* data);
	~VertexBuffer();

	void Bind();
	void UnBind();
};
#endif
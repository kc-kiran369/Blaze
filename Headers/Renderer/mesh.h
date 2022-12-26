#ifndef MESH_H
#define MESH_H

#include <glew/glew.h>

#include <vector>
#include <iostream>

#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include"Texture.h"
#include"Shader.h"

struct Vertex 
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

class Mesh {
public:
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	std::vector<Texture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::vector<Texture> textures);
	~Mesh();
	void Draw(Shader& shader);

private:
	uint32_t VAO, VBO, EBO;

	void setupMesh();
};
#endif
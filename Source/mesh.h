#ifndef MESH_H
#define MESH_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include <glew/glew.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

class Mesh {
public:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices);
	~Mesh();
	void Draw();

private:
	unsigned int VAO, VBO, EBO;

	void setupMesh();
};
#endif
#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifndef STBI_INCLUDE_STB_IMAGE_H
#include "stb_image/stb_image.h"
#endif

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include"mesh.h"
#include"Texture.h"
#include"Shader.h"

#include <GLEW/glew.h>

#include"Benchmark/Logger.h"

class Model
{
public:
	Model();
	~Model();
	void loadModel(std::string path);
	void Draw(Shader& shader);

	std::vector<Mesh> meshes;
private:
	//std::string directory;
	bool m_Loaded = false;

	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadTextures(aiMaterial* mat, aiTextureType type);
};
#endif
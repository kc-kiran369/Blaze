#ifndef MODEL_H
#define MODEL_H

//#include <string>
//#include <fstream>
//#include <sstream>
#include <iostream>
//#include <map>
#include <vector>

#include <GLEW/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifndef STBI_INCLUDE_STB_IMAGE_H
#include "stb_image/stb_image.h"
#endif

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"

class Model
{
public:
	Model();
	~Model();
	void loadModel(std::string path);
	void Draw();

private:
	std::vector<Mesh> meshes;
	std::string directory;

	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
};
#endif
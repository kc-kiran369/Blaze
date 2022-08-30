#include "model.h"

Model::Model()
{
	std::cout << "MODEL CREATED" << std::endl;
}

Model::~Model()
{
	std::cout << "MODEL DELETED" << std::endl;
}

void Model::loadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs );

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "Model didn't open " << importer.GetErrorString() << std::endl;
		return;
	}
	else
	{
		std::cout << "MODEL IMPORTED" << std::endl;
	}

	directory = path.substr(0, path.find_last_of('/'));
	processNode(scene->mRootNode, scene);
}

void Model::Draw(Shader& shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw(shader);
	}
}
void Model::processNode(aiNode* node, const aiScene* scene)
{
	aiMesh* mesh;
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	Vertex vertex;
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{

		//Set Position
		vertex.Position = glm::vec3(
			mesh->mVertices[i].x,
			mesh->mVertices[i].y,
			mesh->mVertices[i].z
		);

		//Set Normals
		vertex.Normal = glm::vec3(
			mesh->mNormals[i].x,
			mesh->mNormals[i].y,
			mesh->mNormals[i].z
		);

		//Set TexturesCoordinate
		if (mesh->mTextureCoords[0])
		{
			vertex.TexCoords = glm::vec2(
				mesh->mTextureCoords[0][i].x,
				mesh->mTextureCoords[0][i].y
			);
		}
		else
		{
			vertex.TexCoords = glm::vec2(0.0f);
		}

		vertices.push_back(vertex);
	}

	//Process indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	//Process Materials
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		//diffuse map
		std::vector<Texture> diffuseMaps = loadTextures(material, aiTextureType_DIFFUSE);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		//specular map
		std::vector<Texture> specularMaps = loadTextures(material, aiTextureType_SPECULAR);
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadTextures(aiMaterial* mat, aiTextureType type)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		std::cout << str.C_Str() << std::endl;
	}
	return textures;
}
#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<string>
#include"glew/glew.h"
#include"glm/matrix.hpp"
#include"ShaderUtils.h"

class Shader
{
public:
	unsigned int ID;
	std::string VertexShader;
	std::string FragmentShader;
	Shader(const char* vert_path, const char* frag_path);

	void Activate();
	void DeActivate();
	void Delete();

};

#endif
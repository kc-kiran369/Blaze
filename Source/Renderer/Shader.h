#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include"glew/glew.h"
#include<string>
#include"glm/matrix.hpp"
#include"Renderer/ShaderUtils.h"

class Shader
{
public:
	unsigned int ID;
	Shader(const char* vert_path, const char* frag_path);

	void Activate();
	void DeActivate();
	void Delete();

	unsigned int GetUniformLocation(const char* name);

	void SetVec3(const char* name, float v1, float v2, float v3);
	void SetVec4(const char* name, float v1, float v2, float v3, float v4);
	void SetFloat(const char* name, float v);
};
#endif
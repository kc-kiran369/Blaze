#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include"glew/glew.h"
#include<string>
#include"ShaderUtils.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

class Shader
{
public:
	unsigned int ID;
	Shader() = default;
	Shader(const char* vert_path, const char* frag_path);

	void Load(const char* vert_path, const char* frag_path);

	void Activate();
	void DeActivate();

	unsigned int GetUniformLocation(const char* name);

	void SetVec3(const char* name, float v1, float v2, float v3);
	void SetVec4(const char* name, float v1, float v2, float v3, float v4);
	void SetFloat(const char* name, float v);
	void SetMat4(const char* name, glm::mat4& mat);
};
#endif
#include"Renderer/Shader.h"

Shader::Shader(const char* vert_path, const char* frag_path)
{
	Load(vert_path, frag_path);
}

void Shader::Load(const char* vert_path, const char* frag_path)
{
	std::string VertexShader = ShaderReader(vert_path);
	std::string FragmentShader = ShaderReader(frag_path);
	ID = CreateShader(VertexShader, FragmentShader);
	glUseProgram(ID);
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::DeActivate()
{
	glDeleteProgram(ID);
}

unsigned int Shader::GetUniformLocation(const char* name)
{
	unsigned int location = glGetUniformLocation(ID, name);
	return location;
}

void Shader::SetVec4(const char* name, float v1, float v2, float v3, float v4)
{
	glUniform4f(GetUniformLocation(name), v1, v2, v3, v4);
}

void Shader::SetVec3(const char* name, float v1, float v2, float v3)
{
	glUniform3f(GetUniformLocation(name), v1, v2, v3);
}

void Shader::SetFloat(const char* name, float v)
{
	glUniform1f(GetUniformLocation(name), v);
}

void Shader::SetMat4(const char* name, glm::mat4& mat)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
}
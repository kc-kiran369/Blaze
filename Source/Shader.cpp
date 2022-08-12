#include"Shader.h"
#include"ShaderUtils.h"

Shader::Shader(const char* vert_path, const char* frag_path)
{
	VertexShader = ParseShader(vert_path);
	FragmentShader = ParseShader(frag_path);
	ID = CreateShader(VertexShader, FragmentShader);
	glUseProgram(ID);
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::DeActivate()
{
	glUseProgram(0);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}
#include"Shader.h"


Shader::Shader(const char* vert_path, const char* frag_path)
{
	VertexShader = ParseShader(vert_path);
	FragmentShader = ParseShader(frag_path);
	ID = CreateShader(VertexShader, FragmentShader);
	glUseProgram(ID);

	std::cout << "Shader Created : "<< ID<< std::endl;
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

unsigned int Shader::GetUniformLocation(const std::string& name)
{
	unsigned int location = glGetUniformLocation(ID, name.c_str());
	return location;
}

void Shader::SetVec4(float *vec4)
{
	glUniform4f(GetUniformLocation("_ambientColor"),vec4[0], vec4[1], vec4[2], vec4[3]);
}
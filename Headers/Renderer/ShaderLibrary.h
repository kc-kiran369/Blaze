#ifndef SHADER_LIBRARY_H
#define SHADER_LIBRARY_H

#include<iostream>
#include<unordered_map>

#include"../Renderer/Shader.h"

class ShaderLibrary
{
private:
	std::unordered_map <std::string, Shader> m_Registry;
public:
	Shader& GetShader(std::string&& ShaderName);
	void AddShader(std::string&& name, const char* vs, const char* fs);

	uint32_t GetCount();
	std::unordered_map<std::string, Shader>& GetRegistry();
};

#endif // !SHADER_LIBRARY_H
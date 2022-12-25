#include"Renderer/ShaderLibrary.h"

Shader& ShaderLibrary::GetShader(std::string&& ShaderName)
{
	return m_Registry[ShaderName];
}

void ShaderLibrary::AddShader(std::string&& name, const char* vs, const char* fs)
{
	if (m_Registry.find(name) == m_Registry.end())
		m_Registry[name] = Shader(vs, fs);
	else
		Logger::Warn("Shader already exists");
}

uint32_t ShaderLibrary::GetCount()
{
	return m_Registry.size();
}

std::unordered_map<std::string, Shader>& ShaderLibrary::GetRegistry()
{
	return m_Registry;
}
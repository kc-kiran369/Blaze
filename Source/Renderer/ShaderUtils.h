#ifndef SHADER_UTILS_CLASS_H
#define SHADER_UTILS_CLASS_H

#include"glew/glew.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include"Benchmark/Logger.h"

uint32_t CompileShader(uint32_t type, std::string& src);

uint32_t CreateShader(std::string& vertexSrc, std::string& fragmentSrc);

std::string ShaderReader(const char* path);
#endif
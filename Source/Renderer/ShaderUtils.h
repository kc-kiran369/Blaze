#ifndef SHADER_UTILS_CLASS_H
#define SHADER_UTILS_CLASS_H

#include"glew/glew.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include"Benchmark/Logger.h"

unsigned int CompileShader(unsigned int type, std::string& src);

unsigned int CreateShader(std::string& vertexSrc, std::string& fragmentSrc);

std::string ParseShader(const char* path);
#endif
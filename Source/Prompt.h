#ifndef PROMPT_H
#define PROMPT_H

#include <Windows.h>
#include<WinUser.h>

#include <glfw/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <glfw/glfw3native.h>

class Prompt
{
public:
	static int Open(GLFWwindow* window, const char* description, const char* title, unsigned int type);
};

#endif
#include"Windows/Prompt.h"

int Prompt::Open(GLFWwindow* window, const char* description, const char* title, unsigned int type)
{
	int result = MessageBoxA(glfwGetWin32Window(window), description, title, type);
	return result;
}
#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <string>

#include <Windows.h>
#include <commdlg.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include<iostream>
#include<glfw/glfw3.h>

class FileDialog
{
public:
	static std::string OpenFile(const char* filter, GLFWwindow* window);
	static std::string SaveFile(const char* filter, GLFWwindow* window);
};
#endif
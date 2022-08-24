#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include"WindowManager.h"
#include <string>

class FileDialog
{
public:
	static std::string OpenFile(const char* filter, GLFWwindow* window);
	static std::string SaveFile(const char* filter, GLFWwindow* window);
};
#endif
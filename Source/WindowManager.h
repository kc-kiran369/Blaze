#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include<glfw/glfw3.h>

class WindowManager
{
public:
	WindowManager();
	~WindowManager();

	void OnAttach();
	void OnDetach();
	void Begin();
	void End();

	GLFWwindow* GetWindow();

	void SetIcon(GLFWwindow* window);

private:
	GLFWwindow* window;
};
#endif
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
	void OnUpdate();
	void OnUpdateComplete();

	float deltaTime();

	GLFWwindow* GetWindow();

	void SetIcon(GLFWwindow* window);

private:
	GLFWwindow* window;
	float currTime = 0.0f, preTime = 0.0f, timeDiff = 0.0f;
};
#endif
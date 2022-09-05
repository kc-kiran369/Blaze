#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include<iostream>
#include<glfw/glfw3.h>
#ifndef STB_IMAGE_IMPLEMENTATION
#include"stb_image/stb_image.h"
#endif
#include"Benchmark/Logger.h"

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
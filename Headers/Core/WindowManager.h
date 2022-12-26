#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include<iostream>
#include<glew/glew.h>
#include<glfw/glfw3.h>
#ifndef STBI_INCLUDE_STB_IMAGE_H
#include"stb_image/stb_image.h"
#endif
#include"Benchmark/Logger.h"

class WindowManager
{
public:
	WindowManager(const char* name, uint16_t width, uint16_t height);
	~WindowManager();

	void OnAttach();
	void OnDetach();
	void OnUpdate();
	void OnUpdateComplete();

	float deltaTime();
	float LastFrameTime();

	GLFWwindow* GetWindow();

	void SetIcon();
	void ToggleSystemConsole();

	uint32_t GetWidth();
	uint32_t GetHeight();

private:
	GLFWwindow* m_Window;
	float m_CurrTime = 0.0f, m_PreTime = 0.0f, m_TimeDiff = 0.0f;
	uint32_t m_Width = 1280, m_Height = 720;
};
#endif
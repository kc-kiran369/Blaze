#include "WindowManager.h"
#include"stb_image/stb_image.h"
#include<iostream>
#include"Logger.h"

WindowManager::WindowManager()
{
	glfwInit();
	window = glfwCreateWindow(1000, 1000, "Blaze", nullptr, nullptr);
	if (window)
		Logger::Info("Window initialized");
	else
		Logger::Error("Window didn't create");
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/
}

WindowManager::~WindowManager()
{
	Logger::Info("Window Manager Out Of Scope...");
}

void WindowManager::OnAttach()
{
	this->SetIcon(this->GetWindow());
	//glfwMaximizeWindow(this->GetWindow());
	glfwMakeContextCurrent(this->GetWindow());
	glfwSwapInterval(1);

	Logger::Info("Version : %s", glGetString(GL_VERSION));
	Logger::Info("Manufacturer : %s", glGetString(GL_RENDERER));
	Logger::Info("Vendor : %s", glGetString(GL_VENDOR));
}

void WindowManager::OnDetach()
{
	glfwTerminate();
}

void WindowManager::OnUpdate()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(32.0f / 255.0f, 32.0f / 255.0f, 32.0f / 255.0f, 1.0f);
	currTime = glfwGetTime();
	timeDiff = currTime - preTime;
}

void WindowManager::OnUpdateComplete()
{
	glfwPollEvents();
	glfwSwapBuffers(this->GetWindow());
	preTime = currTime;
}

float WindowManager::deltaTime()
{
	return (1 / timeDiff);
}

GLFWwindow* WindowManager::GetWindow()
{
	return window;
}

void WindowManager::SetIcon(GLFWwindow* window)
{
	GLFWimage images;
	images.pixels = stbi_load("Resources\\Icon\\Logo_001.png", &images.width, &images.height, 0, 4);
	glfwSetWindowIcon(window, 1, &images);
	stbi_image_free(images.pixels);
}
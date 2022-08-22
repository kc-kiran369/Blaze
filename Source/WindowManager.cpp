#include "WindowManager.h"
#include"stb_image/stb_image.h"
#include<iostream>

WindowManager::WindowManager()
{
	glfwInit();
	window = glfwCreateWindow(800, 800, "Blaze", nullptr, nullptr);
	std::cout << "Window Manager Initialized..." << std::endl;
}

WindowManager::~WindowManager()
{
	std::cout << "Window Manager Out Of Scope..." << std::endl;
}

void WindowManager::OnAttach()
{
	this->SetIcon(this->GetWindow());

	//glfwSetFramebufferSizeCallback(this->GetWindow(), framebuffer_size_callback);
	glfwMaximizeWindow(this->GetWindow());

	glfwMakeContextCurrent(this->GetWindow());
	glfwSwapInterval(1);
}

void WindowManager::OnDetach()
{
	glfwTerminate();
}

void WindowManager::Begin()
{
}

void WindowManager::End()
{
	glfwPollEvents();
	glfwSwapBuffers(this->GetWindow());
}

GLFWwindow* WindowManager::GetWindow()
{
	return this->window;
}

void WindowManager::SetIcon(GLFWwindow* window)
{
	GLFWimage images;
	images.pixels = stbi_load("Resources\\Icon\\Logo_001.png", &images.width, &images.height, 0, 4);
	glfwSetWindowIcon(window, 1, &images);
	stbi_image_free(images.pixels);
}

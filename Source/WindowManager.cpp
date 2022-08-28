#include "WindowManager.h"
#include"stb_image/stb_image.h"
#include<iostream>

WindowManager::WindowManager()
{
	glfwInit();
	window = glfwCreateWindow(1000, 1000, "Blaze", nullptr, nullptr);
	std::cout << (window ? "Window initialized.." : "[Error : Window didn't created]") << std::endl;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	
}

WindowManager::~WindowManager()
{
	std::cout << "Window Manager Out Of Scope..." << std::endl;
}

void WindowManager::OnAttach()
{
	this->SetIcon(this->GetWindow());

	//glfwMaximizeWindow(this->GetWindow());

	glfwMakeContextCurrent(this->GetWindow());
	glfwSwapInterval(1);

	std::cout << "Version : " << glGetString(GL_VERSION) << std::endl;
	std::cout << "Manufacturer : " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Vendor : " << glGetString(GL_VENDOR) << std::endl;
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
	return window;
}

void WindowManager::SetIcon(GLFWwindow* window)
{
	GLFWimage images;
	images.pixels = stbi_load("Resources\\Icon\\Logo_001.png", &images.width, &images.height, 0, 4);
	glfwSetWindowIcon(window, 1, &images);
	stbi_image_free(images.pixels);
}

#include"iostream"

#include"glew/glew.h"
#include"glfw/glfw3.h"
#include"CoreUI.h"

int main()
{
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(600, 600, "Blaze", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	CoreUI ui;
	ui.OnAttach(window);


	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.5f, 0.25f, 0.125f, 1.0f);
		ui.Begin();

		ImGui::Begin("Main");
		ImGui::Text("Blaze Initializing........");
		ImGui::End();

		ui.End();
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	ui.OnDetach();
	glfwTerminate();
}
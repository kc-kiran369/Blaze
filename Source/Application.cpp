#include"iostream"

#define STB_IMAGE_IMPLEMENTATION

#include"glew/glew.h"
#include"glfw/glfw3.h"
#include"CoreUI.h"
#include"Texture.h"
#include"Camera.h"

#include"Model.h"

int main()
{
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(600, 600, "Blaze", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	CoreUI ui;
	ui.OnAttach(window);
	glewInit();

	Camera mainCamera(600, 600, glm::vec3{ 0.0f, 1.0f, -2.0f });
	mainCamera.UpdateMatrix(45.0f, 0.1f, 100.0f);


	Shader shader("shader\\default.vert", "shader\\default.frag");
	Model model;
	model.loadModel("Resources\\Models\\Land.fbx");
	Texture toTheStrayDogs("Resources\\Images\\dazai.png", 1);


	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.5f, 0.25f, 0.125f, 1.0f);
		ui.Begin();

		model.Draw();

		ImGui::Begin("Main");
		ImGui::Image((void*)toTheStrayDogs.GetRendererID(), ImVec2{ (float)toTheStrayDogs.GetWidth(),(float)toTheStrayDogs.GetHeight() });
		ImGui::End();

		ui.End();
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	ui.OnDetach();
	glfwTerminate();
}
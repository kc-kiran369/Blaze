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

	Camera mainCamera(600, 600, glm::vec3{ 0.0f, 2.0f, -2.0f });
	mainCamera.UpdateMatrix(45.0f, 0.1f, 10000.0f);

	Shader shader("Source\\shader\\default.vert", "Source\\shader\\default.frag");
	Model model;
	model.loadModel("Resources\\Models\\Land.fbx");

	glm::mat4 _model = glm::mat4(1.0f);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.16f, 0.16f, 0.125f, 1.0f);
		ui.Begin();
		mainCamera.Input(window);
		mainCamera.SendMVP(shader, "MVP", &_model[0][0]);
		mainCamera.UpdateMatrix(45.0f, 0.1f, 10000.0f);

		model.Draw(shader);

		ui.End();
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	ui.OnDetach();
	glfwTerminate();
}
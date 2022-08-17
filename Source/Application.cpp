#include"iostream"

#define STB_IMAGE_IMPLEMENTATION

#include"glew/glew.h"
#include"glfw/glfw3.h"
#include"CoreUI.h"
#include"Texture.h"
#include"Camera.h"

#include"Model.h"

int width = 700, height = 700;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(width, height, "Blaze", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSwapInterval(1);
	CoreUI ui;
	ui.OnAttach(window);
	glewInit();

	Camera mainCamera(width, height, glm::vec3{ 0.0f, 0.0f, -1.0f });

	Shader shader("Source\\shader\\default.vert", "Source\\shader\\default.frag");
	Model model;
	model.loadModel("Resources\\Models\\Land.fbx");
	Texture texture("Resources\\Images\\Terrain.jpg", 0);
	glActiveTexture(GL_TEXTURE0);

	glm::mat4 _model = glm::mat4(1.0f);

	_model= glm::rotate(_model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.16f, 0.16f, 0.125f, 1.0f);
		ui.Begin();
		mainCamera.UpdateMatrix(45.0f, 0.1f, 1000.0f, _model, shader);

		model.Draw(shader);

		ui.End();
		glfwPollEvents();
		mainCamera.Input(window);
		glfwSwapBuffers(window);
	}

	ui.OnDetach();
	glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
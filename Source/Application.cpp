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
	glEnable(GL_DEPTH_TEST);

	Camera mainCamera(width, height, glm::vec3{ 0.0f, 4.0f, -5.0f });

	Shader shader("Source\\shader\\default.vert", "Source\\shader\\default.frag");
	Model model;
	model.loadModel("Resources\\Models\\Medievalhouse.fbx");
	Texture texture("Resources\\Images\\MedievalhouseDiffuse.jpg", 0);
	glActiveTexture(GL_TEXTURE0);

	glm::mat4 _model = glm::mat4(1.0f);

	_model = glm::rotate(_model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
	float ambientColor[] = { 0.4f,0.4f,0.4f,1.0f };

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.16f, 0.16f, 0.125f, 1.0f);
		ui.Begin();
		mainCamera.UpdateMatrix(45.0f, 0.1f, 1000.0f, _model, shader);
		shader.SetVec4(ambientColor);

		ImGui::BeginMainMenuBar();
		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("Open");
			ImGui::MenuItem("Save as");
			if (ImGui::MenuItem("Exit")) {
				exit(EXIT_SUCCESS);
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("View"))
		{
			ImGui::MenuItem("Hide All Panels");
			ImGui::MenuItem("Property Panel");
			ImGui::MenuItem("Grid");
			ImGui::MenuItem("Zoom in  -");
			ImGui::MenuItem("Zoom out +");
			ImGui::MenuItem("Reset Camera +");
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();

		ImGui::Begin("Lightning");
		if (ImGui::TreeNode("Basic")) {
			ImGui::ColorEdit4("Ambient Color", ambientColor);
			ImGui::TreePop();
		}
		ImGui::End();

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
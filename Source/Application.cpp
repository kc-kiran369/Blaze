#include"iostream"

#define STB_IMAGE_IMPLEMENTATION

#include"glew/glew.h"
#include"glfw/glfw3.h"
#include"CoreUI.h"
#include"Texture.h"
#include"Camera.h"
#include"FrameBuffer.h"

#include"Model.h"

int width = 700, height = 700;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(width, height, "Blaze", nullptr, nullptr);
	/*GLFWimage images[1];
	images[0].pixels = stbi_load("Resources\\Icon\\Logo.png", &images[0].width, &images[0].height, 0, 4);
	glfwSetWindowIcon(window, 1, images);
	stbi_image_free(images[0].pixels);*/

	GLFWimage images;
	images.pixels = stbi_load("Resources\\Icon\\Logo.png", &images.width, &images.height, 0, 4);
	glfwSetWindowIcon(window, 1, &images);
	stbi_image_free(images.pixels);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSwapInterval(1);
	CoreUI ui;
	ui.OnAttach(window);
	glewInit();

	Camera mainCamera(width, height, glm::vec3{ 0.0f, 4.0f, -5.0f });

	Shader shader("Source\\shader\\default.vert", "Source\\shader\\default.frag");
	Model model, cube, land, monkey;
	cube.loadModel("Resources\\Models\\Cube.fbx");
	land.loadModel("Resources\\Models\\Land.fbx");
	monkey.loadModel("Resources\\Models\\Monkey.fbx");
	Texture texture("Resources\\Images\\MedievalhouseDiffuse.jpg", 0);
	glBindTexture(GL_TEXTURE_2D, texture.GetRendererID());

	glm::mat4 _model = glm::mat4(1.0f);
	_model = glm::rotate(_model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));

	float ambientColor[] = { 0.4f,0.4f,0.4f,1.0f };

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.16f, 0.16f, 0.125f, 1.0f);
		mainCamera.UpdateMatrix(45.0f, 0.1f, 1000.0f, _model, shader);

		shader.SetVec4(ambientColor);

		model.Draw(shader);
		cube.Draw(shader);
		land.Draw(shader);
		monkey.Draw(shader);

		ui.Begin();
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
		if (ImGui::BeginMenu("Add"))
		{
			ImGui::MenuItem("Cube");
			ImGui::MenuItem("Cylinder");
			ImGui::MenuItem("Sphere");
			if (ImGui::MenuItem("Import Model.."))
			{
				model.loadModel("Resources\\Models\\Medievalhouse.fbx");
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
		if (ImGui::Begin("ToolBar", (bool*)0, ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize |
			ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoMove))
		{
			ImGui::SetWindowPos(ImVec2{ 0.0f,30.0f });
			ImGui::Button("T", ImVec2{ 40.0f,40.0f });
			ImGui::Button("R", ImVec2{ 40.0f,40.0f });
			ImGui::Button("S", ImVec2{ 40.0f,40.0f });
			ImGui::End();
		}
		if (ImGui::Begin("Lightning"))
		{
			if (ImGui::TreeNode("Basic")) {
				ImGui::ColorEdit4("Ambient Color", ambientColor);
				ImGui::TreePop();
			}
			ImGui::End();
		}

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
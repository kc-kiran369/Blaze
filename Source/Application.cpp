#define STB_IMAGE_IMPLEMENTATION

#include"iostream"

#include"glew/glew.h"
#include"glfw/glfw3.h"

#include"CoreUI.h"
#include"Texture.h"
#include"Camera.h"
#include"FrameBuffer.h"
#include"WindowManager.h"
#include"Model.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
	WindowManager winManager;
	winManager.OnAttach();

	CoreUI ui;
	ui.OnAttach(winManager.GetWindow());
	glewInit();

	Camera mainCamera(800,800, glm::vec3{ 0.0f, 4.0f, -5.0f });

	Texture moveIcon("Resources\\Icon\\MoveIcon.png", NULL);
	Texture rotateIcon("Resources\\Icon\\RotateIcon.png", NULL);
	Texture scaleIcon("Resources\\Icon\\ScaleIcon.png", NULL);

	Shader shader("Source\\shader\\default.vert", "Source\\shader\\default.frag");
	Model model;
	Texture texture("Resources\\Images\\MedievalhouseDiffuse.jpg", 0);
	texture.Bind();

	glm::mat4 _model = glm::mat4(1.0f);
	_model = glm::rotate(_model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));

	float ambientColor[] = { 0.4f,0.4f,0.4f,1.0f };

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(winManager.GetWindow()))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.16f, 0.16f, 0.125f, 1.0f);
		mainCamera.UpdateMatrix(45.0f, 0.1f, 1000.0f, _model, shader);

		shader.SetVec4("_ambientColor", ambientColor[0], ambientColor[1], ambientColor[2], ambientColor[3]);

		model.Draw(shader);

		ui.Begin();
		ImGui::BeginMainMenuBar();
		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("Open", "Ctrl+o");
			ImGui::MenuItem("Save as", "Ctrl+s");
			if (ImGui::MenuItem("Exit", "Ctrl+q")) {
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
			if (ImGui::BeginMenu("Mesh"))
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
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
		if (ImGui::Begin("ToolBar", (bool*)0, ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize |
			ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoMove))
		{
			ImGui::SetWindowPos(ImVec2{ 0.0f,30.0f });

			if (ImGui::ImageButton((void*)moveIcon.GetRendererID(), ImVec2{ 20.0f,20.0f }))
			{
				std::cout << "Transform Tool Selected" << std::endl;
			}
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::TextUnformatted("Move");
				ImGui::EndTooltip();
			}
			if (ImGui::ImageButton((void*)rotateIcon.GetRendererID(), ImVec2{ 20.0f,20.0f }))
			{
				std::cout << "Rotate Tool Selected" << std::endl;
			}
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::TextUnformatted("Rotate");
				ImGui::EndTooltip();
			}
			if (ImGui::ImageButton((void*)scaleIcon.GetRendererID(), ImVec2{ 20.0f,20.0f }))
			{
				std::cout << "Scale Tool Selected" << std::endl;
			}
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::TextUnformatted("Scale");
				ImGui::EndTooltip();
			}
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
		mainCamera.Input(winManager.GetWindow());
		winManager.End();
	}

	ui.OnDetach();
	winManager.OnDetach();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
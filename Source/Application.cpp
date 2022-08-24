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
#include"FileDialog.h"

int main()
{
	WindowManager winManager;
	winManager.OnAttach();

	CoreUI ui;
	ui.OnAttach(winManager.GetWindow());
	glewInit();

	Camera mainCamera(800, 800, glm::vec3{ 1.0f, 4.0f, -15.0f });

	Shader defaultShader("Shader\\default.vert", "Shader\\default.frag");
	Model model;
	Texture texture("Resources\\Images\\MedievalhouseDiffuse.jpg", 0);

	glm::mat4 _model = glm::mat4(1.0f);
	model.loadModel("Resources\\Models\\Medievalhouse.fbx");
	_model = glm::rotate(_model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));

	float ambientColor[] = { 0.4f,0.4f,0.4f,1.0f };

	FrameBuffer framerBuffer;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	while (!glfwWindowShouldClose(winManager.GetWindow()))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.16f, 0.16f, 0.125f, 1.0f);
		mainCamera.UpdateMatrix(45.0f, 0.1f, 1000.0f, _model, defaultShader);

		defaultShader.SetVec4("_ambientColor", ambientColor[0], ambientColor[1], ambientColor[2], ambientColor[3]);

#pragma region GUI
		ui.Begin();
		ImGui::BeginMainMenuBar();
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open", "Ctrl+O"))
			{
				FileDialog::OpenFile(".png,.jpg", winManager.GetWindow());
				FileDialog::SaveFile(".png,.jpg", winManager.GetWindow());
			}
			ImGui::MenuItem("New", "Ctrl+N");
			ImGui::MenuItem("Save as", "Ctrl+S");
			if (ImGui::MenuItem("Exit", "Ctrl+Q")) {
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
#pragma endregion

		if (ImGui::Begin("Lightning"))
		{
			if (ImGui::TreeNode("Basic")) {
				ImGui::ColorEdit4("Ambient Color", ambientColor);
				ImGui::TreePop();
			}
			ImGui::End();
		}

		if (ImGui::Begin("Viewport", (bool*)0, ImGuiWindowFlags_NoResize))
		{
			ImGui::Image((void*)framerBuffer.GetColorTexture(), ImVec2{ ImGui::GetWindowWidth(),ImGui::GetWindowHeight() });
			ImGui::End();
		}

		if (ImGui::Begin("Console"))
		{
			ImGui::Text("Messages..");
			ImGui::End();
		}

		framerBuffer.Bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.16f, 0.16f, 0.125f, 1.0f);
		texture.Bind();
		model.Draw(defaultShader);
		framerBuffer.UnBind();

		ui.End();
		mainCamera.Input(winManager.GetWindow());
		winManager.End();
	}

	ui.OnDetach();
	winManager.OnDetach();
}
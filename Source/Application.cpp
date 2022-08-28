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

int main(int args, char** argv)
{
	std::cout << argv[0] << std::endl;
	WindowManager winManager;
	winManager.OnAttach();

	CoreUI ui;
	ui.OnAttach(winManager.GetWindow());
	glewInit();

	Camera mainCamera(1000, 1000, glm::vec3{ 5.0f, 5.0f, -15.0f });

	Shader defaultShader("Shader\\default.vert", "Shader\\default.frag");
	Shader brightShader("Shader\\default.vert", "Shader\\BrightColor.frag");
	Model model;
	Texture texture("Resources\\Images\\MedievalhouseDiffuse.jpg", 0);

	glm::mat4 _model = glm::mat4(1.0f);
	_model = glm::rotate(_model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));

	float ambientColor[] = { 0.4f,0.4f,0.4f,1.0f };

	FrameBuffer framerBuffer;

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_ALWAYS);
	glDepthFunc(GL_LESS);

	float currTime = 0.0f, preTime = 0.0f, timeDiff = 0.0f;

	while (!glfwWindowShouldClose(winManager.GetWindow()))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.16f, 0.16f, 0.125f, 1.0f);
		mainCamera.UpdateMatrix(45.0f, 0.1f, 1000.0f, _model, defaultShader);

		defaultShader.SetVec4("_ambientColor", ambientColor[0], ambientColor[1], ambientColor[2], ambientColor[3]);

		currTime = glfwGetTime();
		timeDiff = currTime - preTime;

		ui.Begin();
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				ImGui::MenuItem("Open", "Ctrl+O");
				ImGui::MenuItem("New", "Ctrl+N");
				ImGui::MenuItem("Save as", "Ctrl+S");
				if (ImGui::MenuItem("Exit", "Ctrl+Q"))
				{
					exit(EXIT_SUCCESS);
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::MenuItem("Preferences"))
				{

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
				ImGui::MenuItem("Cone");
				ImGui::MenuItem("Cylinder");
				ImGui::MenuItem("Sphere");
				if (ImGui::MenuItem("Import Model.."))
				{
					std::string path = FileDialog::OpenFile("*.fbx\0", winManager.GetWindow());
					model.loadModel(path);
				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		ImGui::Begin("Lightning");
		if (ImGui::TreeNode("Basic")) {
			ImGui::ColorEdit4("Ambient Color", ambientColor, ImGuiColorEditFlags_NoInputs);
			ImGui::TreePop();
		}
		ImGui::End();

		ImGui::Begin("Viewport", (bool*)0, ImGuiWindowFlags_NoResize);
		ImGui::Text("FPS : %f", (1 / timeDiff));
		ImGui::Image((void*)framerBuffer.GetColorTexture(), ImVec2{ ImGui::GetWindowWidth(),ImGui::GetWindowHeight() });
		ImGui::End();

		ImGui::Begin("Camera Settings");
		ImGui::SliderFloat("Sensitivity", &mainCamera.sensitivity, 20.0f, 50.0f, std::to_string(mainCamera.sensitivity).c_str(), 1.0f);
		ImGui::SliderFloat("Speed", &mainCamera.speed, 0.01f, 1.0f, std::to_string(mainCamera.speed).c_str(), 1.0f);
		ImGui::End();

		ImGui::Begin("Hierarchy");
		ImGui::Text("Entity 1");
		ImGui::Text("Entity 2");
		ImGui::Text("Entity 3");
		ImGui::End();

		ImGui::Begin("Inspector");
		ImGui::Text("Entity Name");
		if (ImGui::Button("Add Component"))
		{

		}
		ImGui::Text("Transform");
		ImGui::Text("Mesh Filter");
		ImGui::Text("Mesh Renderer");
		ImGui::End();

		framerBuffer.Bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.16f, 0.16f, 0.125f, 1.0f);
		texture.Bind();
		model.Draw(defaultShader);
		framerBuffer.UnBind();

		ui.End();
		mainCamera.Input(winManager.GetWindow());
		winManager.End();
		preTime = currTime;
	}

	ui.OnDetach();
	winManager.OnDetach();
}
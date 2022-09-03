#define STB_IMAGE_IMPLEMENTATION

#include"iostream"
#include<thread>

#include"glew/glew.h"
#include"glfw/glfw3.h"

#include"CoreUI.h"
#include"Texture.h"
#include"Camera.h"
#include"FrameBuffer.h"
#include"WindowManager.h"
#include"Model.h"
#include"FileDialog.h"
#include"Prompt.h"

#include"../tests/Scene.h"
#include"../tests/Entity.h"

#include"Logger.h"

int main(int args, char** argv)
{
	Logger::Info(argv[0]);
	WindowManager winManager;
	winManager.OnAttach();

	CoreUI ui;
	ui.OnAttach(winManager.GetWindow());
	glewInit();

	Scene mainScene;
	Entity* activeEnt = nullptr;

	Camera mainCamera(1000, 1000, glm::vec3{ 5.0f, 5.0f, -15.0f });

	Shader defaultShader("Shader\\default.vert", "Shader\\default.frag");
	Shader brightShader("Shader\\default.vert", "Shader\\BrightColor.frag");
	Model model;
	Texture texture("Resources\\Images\\MedievalhouseDiffuse.jpg", 0);

	glm::mat4 _model = glm::mat4(1.0f);
	_model = glm::rotate(_model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));

	float ambientColor[] = { 0.4f,0.4f,0.4f,1.0f };

	FrameBuffer framerBuffer;

	char name[15] = { 0 };


	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(winManager.GetWindow()))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(32.0f / 255.0f, 32.0f / 255.0f, 32.0f / 255.0f, 1.0f);
		mainCamera.UpdateMatrix(45.0f, 0.1f, 1000.0f, _model, defaultShader);

		defaultShader.SetVec4("_ambientColor", ambientColor[0], ambientColor[1], ambientColor[2], ambientColor[3]);

		winManager.OnUpdate();

		ui.Begin();

#pragma region MainMenuBar
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				ImGui::MenuItem("Open", "Ctrl+O");
				ImGui::MenuItem("New", "Ctrl+N");
				ImGui::MenuItem("Save as", "Ctrl+S");
				if (ImGui::MenuItem("Exit", "Ctrl+Q"))
				{
					if (Prompt::Open(winManager.GetWindow(), "Any unsaved progress will be lost", "Are you sure want to exit!!", MB_YESNO | MB_ICONINFORMATION) == IDYES)
					{
						glfwSetWindowShouldClose(winManager.GetWindow(), 1);
					}
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
				if (ImGui::MenuItem("Empty Entity"))
				{

				}
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
#pragma endregion

		ImGui::Begin("Lightning");
		if (ImGui::TreeNode("Basic")) {
			ImGui::ColorEdit4("Ambient Color", ambientColor, ImGuiColorEditFlags_NoInputs);
			ImGui::TreePop();
		}
		ImGui::End();

		ImGui::Begin("Viewport", (bool*)0, ImGuiWindowFlags_NoResize);
		ImGui::Image((ImTextureID)framerBuffer.GetColorTexture(), ImVec2{ 1000,1000 });
		ImGui::End();

		ImGui::Begin("Camera Settings");
		ImGui::SliderFloat("Sensitivity", &mainCamera.sensitivity, 20.0f, 50.0f, std::to_string(mainCamera.sensitivity).c_str(), 1.0f);
		ImGui::SliderFloat("Speed", &mainCamera.speed, 0.01f, 1.0f, std::to_string(mainCamera.speed).c_str(), 1.0f);
		ImGui::End();

		ImGui::Begin("Hierarchy");
		ImGui::Text("Total entities : %d", mainScene.m_Registry.size());
		auto view = mainScene.m_Registry.view<Tag>();
		for (auto entity : view)
		{
			if (ImGui::MenuItem(view.get<Tag>(entity).tag))
			{
				activeEnt->m_Entity = entity;

			}
		}

		if (ImGui::BeginPopupContextWindow(0, ImGuiMouseButton_Right, false))
		{
			if (ImGui::MenuItem("Empty Entity"))
			{
				Entity* temp = mainScene.CreateEntity();
				activeEnt = temp;
			}
			if (ImGui::MenuItem("Cube")) {}
			if (ImGui::MenuItem("Cylinder")) {}
			if (ImGui::MenuItem("Sphere")) {}
			if (ImGui::MenuItem("Cone")) {}
			if (ImGui::MenuItem("Import..")) {}
			ImGui::EndPopup();
		}
		ImGui::End();

		ImGui::Begin("Inspector");
		if (activeEnt)
		{
			ImGui::Text(activeEnt->GetComponent<Tag>().tag);

			if (ImGui::InputText("Rename", name, sizeof(name)))
			{
				if (name[0] != '\0')
				{
					activeEnt->GetComponent<Tag>().tag = name;
				}
			}

			if (!activeEnt->HasComponent<Transform>())
				ImGui::Text("No Transform Component");
			else
			{
				ImGui::BeginGroup();
				ImGui::Text("Transform");

				ImGui::DragFloat("X", &activeEnt->GetComponent<Transform>().transform.X, 0.1f);
				ImGui::DragFloat("Y", &activeEnt->GetComponent<Transform>().transform.Y, 0.1f);
				ImGui::DragFloat("Z", &activeEnt->GetComponent<Transform>().transform.Z, 0.1f);
				ImGui::EndGroup();
			}

			if (!activeEnt->HasComponent<Renderer>())
				ImGui::Text("No Renderer Component");
			else
			{
				ImGui::Text("Renderer");
				if (ImGui::Button("Select Mesh"))
				{
					activeEnt->GetComponent<Renderer>().model.loadModel(FileDialog::OpenFile("*.fbx\0", winManager.GetWindow()));
				}
			}
		}
		ImGui::End();

		ImGui::Begin("Profiler");
		ImGui::Text("FPS : %f", winManager.deltaTime());
		ImGui::End();

		framerBuffer.Bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.16f, 0.16f, 0.125f, 1.0f);
		texture.Bind();
		for (auto entity : mainScene.entities)
		{
			entity->GetComponent<Renderer>().model.Draw(defaultShader);
		}
		model.Draw(defaultShader);
		framerBuffer.UnBind();

		ui.End();
		mainCamera.Input(winManager.GetWindow());
		winManager.OnUpdateComplete();
	}
	ui.OnDetach();
	winManager.OnDetach();
	return EXIT_SUCCESS;
}
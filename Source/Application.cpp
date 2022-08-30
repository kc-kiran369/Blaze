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

#include"../tests/Scene.h"
#include"../tests/Entity.h"

int main(int args, char** argv)
{
	std::cout << argv[0] << std::endl;
	WindowManager winManager;
	winManager.OnAttach();

	CoreUI ui;
	ui.OnAttach(winManager.GetWindow());
	glewInit();

	Scene mainScene;
	std::vector<Entity> entities;
	//Entity* activeOnViewport = nullptr;

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

	float currTime = 0.0f, preTime = 0.0f, timeDiff = 0.0f;

	while (!glfwWindowShouldClose(winManager.GetWindow()))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(32.0f / 255.0f, 32.0f / 255.0f, 32.0f / 255.0f, 1.0f);
		mainCamera.UpdateMatrix(45.0f, 0.1f, 1000.0f, _model, defaultShader);

		defaultShader.SetVec4("_ambientColor", ambientColor[0], ambientColor[1], ambientColor[2], ambientColor[3]);

		currTime = glfwGetTime();
		timeDiff = currTime - preTime;

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
				if (ImGui::MenuItem("Empty Entity"))
				{
					const char* name = "Empty Entity";
					Entity temp = mainScene.CreateEntity();
					temp.AddComponent<Tag>(name);
					entities.push_back(temp);
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
		ImGui::Image((void*)framerBuffer.GetColorTexture(), ImVec2{ 1000,1000 });
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
				//activeOnViewport->m_Entity = entity;
			}
		}
		ImGui::End();

		ImGui::Begin("Inspector");
		/*if (activeOnViewport != nullptr)
			ImGui::Text(activeOnViewport->GetComponent<Tag>().tag);*/
		for (auto entity : entities)
		{
			ImGui::Text(entity.GetComponent<Tag>().tag);
		}

		ImGui::BeginGroup();
		ImGui::Text("Transform");
		float tr[3];
		ImGui::DragFloat3("Transform", tr, 1.0f, 0.0f, 1.0f, "", ImGuiSliderFlags_None);
		ImGui::EndGroup();
		ImGui::Text("Mesh Renderer");
		if (ImGui::BeginCombo("Components", "RigidBody"))
		{
			//ImGui::Combo("Transform",);
			ImGui::MenuItem("Mesh Renderer");
			ImGui::MenuItem("RigidBody");
			ImGui::MenuItem("Mono");
			ImGui::EndCombo();
		}
		if (ImGui::Button("Add Component"))
		{
		}
		ImGui::End();

		ImGui::Begin("Profiler");
		ImGui::Text("FPS : %f", (1 / timeDiff));
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
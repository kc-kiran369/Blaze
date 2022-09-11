#pragma warning (diasble: 26451)
#pragma warning (diasble: 4715)

#define STB_IMAGE_IMPLEMENTATION

#include"Benchmark/AllocationTracer.h"

#include"iostream"
#include<thread>

#include"glew/glew.h"
#include"glfw/glfw3.h"

#include"ECS/Entity.h"
#include"ECS/Scene.h"
#include"ECS/Component/Components.h"
#include"Renderer/Camera.h"
#include"Renderer/FrameBuffer.h"
#include"Renderer/Shader.h"
#include"Renderer/model.h"
#include"Renderer/Texture.h"

#include"Windows/FileDialog.h"
#include"Windows/Prompt.h"

#include"Benchmark/Timer.h"

#include"Benchmark/Logger.h"
#include"Core/WindowManager.h"
#include"UI/CoreUI.h"

#include"Blaze.h"

int main(int args, char** argv)
{
	Logger::Info(argv[0]);
	WindowManager winManager;
	winManager.OnAttach();

	CoreUI ui;
	ui.OnAttach(winManager.GetWindow());
	glewInit();

	Scene mainScene;
	auto view = mainScene.m_Registry.view<Tag>();
	auto Rview = mainScene.m_Registry.view<Renderer>();
	Entity* activeEnt = nullptr;

	Camera mainCamera(1000, 1000, glm::vec3{ 5.0f, 5.0f, -15.0f });

	Shader standardShader("Shader\\standard.vert", "Shader\\standard.frag");
	Texture texture("Resources\\Images\\MedievalhouseDiffuse.jpg", 0);

	glm::mat4 _model = glm::mat4(1.0f);
	_model = glm::rotate(_model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));

	float ambientColor[] = { 0.4f,0.4f,0.4f,1.0f };

	FrameBuffer framerBuffer;

	float lastRenderTime = 0.0f;

	while (!glfwWindowShouldClose(winManager.GetWindow()))
	{
		mainCamera.UpdateMatrix(45.0f, 0.1f, 1000.0f, _model, standardShader);
		winManager.OnUpdate();
		ui.Begin();

		ui.OnGuiUpdate(winManager);

		ImGui::Begin("Camera Debug");
		ImGui::Text("Position X : %.2f Y : %.2f Z : %.2f", mainCamera.Position.x, mainCamera.Position.y, mainCamera.Position.z);
		ImGui::Text("Orientation X : %.2f Y : %.2f Z : %.2f", mainCamera.Orientation.x, mainCamera.Orientation.y, mainCamera.Orientation.z);
		ImGui::Text("Up X : %.2f Y : %.2f Z : %.2f", mainCamera.Up.x, mainCamera.Up.y, mainCamera.Up.z);
		ImGui::End();

		ImGui::Begin("Lightning");
		if (ImGui::TreeNode("Basic")) {
			if (ImGui::ColorEdit4("Ambient Color", ambientColor, ImGuiColorEditFlags_NoInputs))
			{
				standardShader.SetVec4("_ambientColor", ambientColor[0], ambientColor[1], ambientColor[2], ambientColor[3]);
			}
			ImGui::TreePop();
		}
		ImGui::End();

		ImGui::Begin("Viewport", (bool*)0, ImGuiWindowFlags_NoResize);
		ImGui::Image((ImTextureID)framerBuffer.GetColorTexture(), ImVec2{ 1000,1000 });
		ImGui::End();

		ImGui::Begin("Camera Settings");
		ImGui::SliderFloat("Sensitivity", &mainCamera.sensitivity, 20.0f, 50.0f, "%.2f", 1.0f);
		ImGui::SliderFloat("Speed", &mainCamera.speed, 0.01f, 1.0f, "%.3f", 1.0f);
		ImGui::End();

		ImGui::Begin("Hierarchy");
		ImGui::Text("Total entities : %d", mainScene.m_Registry.size());
		for (auto entity : view)
		{

			if (ImGui::MenuItem(view.get<Tag>(entity).tag.c_str(), (const char*)0, (activeEnt ? (activeEnt->GetComponent<Tag>().tag == view.get<Tag>(entity).tag ? true : false) : false), true))
			{
				activeEnt->m_Entity = entity;
			}
		}
		//ImGui::ShowStyleEditor(NULL);

		if (ImGui::BeginPopupContextWindow(0, ImGuiMouseButton_Right, false))
		{
			if (ImGui::MenuItem("Empty Entity"))
			{
				Entity* temp = mainScene.CreateEntity();
				if (mainScene.m_Registry.size() == 1)
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

		ImGui::Begin("Entity Debugger");
		if (activeEnt)
		{
			ImGui::Text("Entity ID : %d", activeEnt->m_Entity);
			ImGui::Text("Entity Name : %s", activeEnt->GetComponent<Tag>().tag.c_str());
		}
		ImGui::End();
		ImGui::Begin("Property");
		if (activeEnt)
		{
			ImGui::Text(activeEnt->GetComponent<Tag>().tag.c_str());
			ImGui::Separator();

			if (!activeEnt->HasComponent<Transform>())
				ImGui::Text("No Transform Component");
			else
			{
				ImGui::Text("Transform");
				ImGui::Separator();
				if (DrawVec3Control("Translation", activeEnt->GetComponent<Transform>().transform, 0.0f, 100.0f))
				{
					standardShader.SetFloat("facX", activeEnt->GetComponent<Transform>().transform.x);
					standardShader.SetFloat("facY", activeEnt->GetComponent<Transform>().transform.y);
					standardShader.SetFloat("facZ", activeEnt->GetComponent<Transform>().transform.z);
				}
				DrawVec3Control("Rotation", activeEnt->GetComponent<Transform>().rotation, 0.0f, 100.0f);
				DrawVec3Control("Scale", activeEnt->GetComponent<Transform>().scale, 0.0f, 100.0f);
				ImGui::Separator();
			}

			if (!activeEnt->HasComponent<Renderer>())
			{
				ImGui::Text("No Renderer Component");
			}
			else
			{
				ImGui::Text("Renderer");
				ImGui::Separator();
				if (activeEnt->GetComponent<Renderer>().hasModel)
					ImGui::Text("It already has model");
				else
				{
					if (ImGui::Button("Select Mesh"))
					{
						activeEnt->GetComponent<Renderer>().model.loadModel(FileDialog::OpenFile("*.fbx\0", winManager.GetWindow()));
						activeEnt->GetComponent<Renderer>().hasModel = true;
					}
				}
				ImGui::Separator();
			}
		}
		ImGui::End();

		ImGui::Begin("Profiler");
		ImGui::Text("FPS : %f", winManager.deltaTime());
		ImGui::Text("Last Render Time : %dms", 0.0f);
		ImGui::End();

		framerBuffer.Bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.16f, 0.16f, 0.125f, 1.0f);
		texture.Bind();
		for (auto ent : Rview)
		{
			Rview.get<Renderer>(ent).model.Draw(standardShader);
		}
		framerBuffer.UnBind();

		ui.End();
		mainCamera.Input(winManager.GetWindow());
		winManager.OnUpdateComplete();
	}
	ui.OnDetach();
	winManager.OnDetach();
	return EXIT_SUCCESS;
}
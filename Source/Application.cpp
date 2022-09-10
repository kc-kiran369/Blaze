#define STB_IMAGE_IMPLEMENTATION

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

#include"Benchmark/AllocationTracer.h"

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
	//Shader brightShader("Shader\\standard.vert", "Shader\\Light.frag");
	Texture texture("Resources\\Images\\MedievalhouseDiffuse.jpg", 0);

	glm::mat4 _model = glm::mat4(1.0f);
	_model = glm::rotate(_model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));

	float ambientColor[] = { 0.4f,0.4f,0.4f,1.0f };

	FrameBuffer framerBuffer;

	char name[15] = { 0 };
	float lastRenderTime = 0.0f;

	while (!glfwWindowShouldClose(winManager.GetWindow()))
	{
		mainCamera.UpdateMatrix(45.0f, 0.1f, 1000.0f, _model, standardShader);
		winManager.OnUpdate();
		ui.Begin();

		ui.OnGuiUpdate(winManager);

		ImGui::Begin("Camera Debug");
		ImGui::Text("Position X : %f Y : %f Z : %f", mainCamera.Position.x, mainCamera.Position.y, mainCamera.Position.z);
		ImGui::Text("Orientation X : %f Y : %f Z : %f", mainCamera.Orientation.x, mainCamera.Orientation.y, mainCamera.Orientation.z);
		ImGui::Text("Up X : %f Y : %f Z : %f", mainCamera.Up.x, mainCamera.Up.y, mainCamera.Up.z);
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

		ImGui::Begin("view view");
		for (auto ent : view)
		{
			ImGui::Text("%s", view.get<Tag>(ent).tag);
		}
		ImGui::End();

		ImGui::Begin("Property");
		if (activeEnt)
		{
			ImGui::Text(activeEnt->GetComponent<Tag>().tag.c_str());

			/*if (ImGui::InputText("Rename", name, sizeof(name)))
			{
				if (name[0] != '\0' || name[0] != 0)
				{
					activeEnt->GetComponent<Tag>().tag = name;
				}
				else
				{
					Logger::Warn("Name is empty");
				}
			}*/

			if (!activeEnt->HasComponent<Transform>())
				ImGui::Text("No Transform Component");
			else
			{
				ImGui::BeginGroup();
				ImGui::Columns(2, 0, false);
				ImGui::Text("Transform");
				ImGui::NextColumn();
				if (ImGui::Button("_X_"))
				{

				}
				ImGui::Columns(1);

				glm::vec3 temp = glm::vec3(0);
				if (ImGui::SliderFloat("x", &temp.x, -10.0f, 10.0f, "%.3f", 1.0f))
				{
					activeEnt->GetComponent<Transform>().transform = temp;
					_model = glm::translate(_model, temp);
				}
				if (ImGui::SliderFloat("y", &temp.y, -100.0f, 100.0f, "%.3f", 1.0f))
					activeEnt->GetComponent<Transform>().transform += temp;
				if (ImGui::SliderFloat("z", &temp.z, -100.0f, 100.0f, "%.3f", 1.0f))
					activeEnt->GetComponent<Transform>().transform += temp;
				ImGui::EndGroup();
			}

			if (!activeEnt->HasComponent<Renderer>())
				ImGui::Text("No Renderer Component");
			else
			{
				ImGui::Text("Renderer");
				if (activeEnt->GetComponent<Renderer>().hasModel)
					ImGui::Text("It already has model");
				else
					if (ImGui::Button("Select Mesh"))
					{
						activeEnt->GetComponent<Renderer>().model.loadModel(FileDialog::OpenFile("*.fbx\0", winManager.GetWindow()));
						activeEnt->GetComponent<Renderer>().hasModel = true;
					}
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
		//for (auto entity : mainScene.entities)
		//{
		//	//Timer timer;
		//	entity->GetComponent<Renderer>().model.Draw(standardShader);
		//	//lastRenderTime = timer.Stop();
		//}
		for (auto ent : Rview)
		{
			Rview.get<Renderer>(ent).model.Draw(standardShader);
		}
		//model.Draw(standardShader);
		framerBuffer.UnBind();

		ui.End();
		mainCamera.Input(winManager.GetWindow());
		winManager.OnUpdateComplete();
	}
	ui.OnDetach();
	winManager.OnDetach();
	return EXIT_SUCCESS;
}
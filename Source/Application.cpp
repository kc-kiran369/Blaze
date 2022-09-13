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
#include"UI/Panel.h"

#include"Blaze.h"

#include"imgizmo/ImGuizmo.h"
#include"im3d/im3d.h"

int main(int args, char** argv)
{
	#pragma region Setup
	WindowManager winManager;
	winManager.OnAttach();

	CoreUI ui;
	ui.OnAttach(winManager.GetWindow());
	glewInit();
	#pragma endregion 

	#pragma region Initilization
	Scene mainScene;
	entt::entity selectedEntity = entt::entity(0);

	Camera mainCamera(1000, 1000, glm::vec3{ 5.0f, 5.0f, -15.0f });

	Shader standardShader("Shader\\standard.vert", "Shader\\standard.frag");
	Texture texture("Resources\\Images\\MedievalhouseDiffuse.jpg", 0);

	glm::mat4 _model = glm::mat4(1.0f);
	_model = glm::rotate(_model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));

	float ambientColor[] = { 0.4f,0.4f,0.4f,1.0f };

	FrameBuffer frameBuffer;
	#pragma endregion

	while (!glfwWindowShouldClose(winManager.GetWindow()))
	{
		mainCamera.UpdateMatrix(45.0f, 0.1f, 1000.0f, _model, standardShader);
		winManager.OnUpdate();
		ui.Begin();

		Blaze::UI::MainMenuBar(winManager);

		Blaze::UI::LightingPanel(standardShader, ambientColor);

		Blaze::UI::ViewportPanel(frameBuffer);

		Blaze::UI::HierarchyPanel(mainScene, selectedEntity);

		Blaze::UI::PropertyPanel(mainScene, selectedEntity, standardShader, winManager.GetWindow());

		Blaze::UI::ProfilerPanel(winManager);

		#pragma region Rendering
		frameBuffer.Bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.16f, 0.16f, 0.125f, 1.0f);
		texture.Bind();
		mainScene.m_Registry.each([&](entt::entity entity)
			{
				mainScene.m_Registry.get<Renderer>(entity).model.Draw(standardShader);
			});
		frameBuffer.UnBind();
		#pragma endregion 

		ui.End();
		mainCamera.Input(winManager.GetWindow());
		winManager.OnUpdateComplete();
	}
	#pragma region CleanUp
	ui.OnDetach();
	winManager.OnDetach();
	return EXIT_SUCCESS;
	#pragma endregion
}
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

#include"Renderer/ShaderLibrary.h"

int main(int args, char** argv)
{
#pragma region Setup
	WindowManager winManager;
	winManager.OnAttach();

	CoreUI ui_interface;
	ui_interface.OnAttach(winManager.GetWindow());
	glewInit();
#pragma endregion 

#pragma region Initilization
	Scene mainScene;

	Camera mainCamera(winManager.width, winManager.height, glm::vec3{ 5.0f, 5.0f, -15.0f });

	ShaderLibrary shaderLibrary;
	shaderLibrary.AddShader("StandardShader", "Shader\\standard.vert", "Shader\\standard.frag");

	Texture texture("Resources\\Images\\MedievalhouseDiffuse.jpg", 0);

	float ambientColor[] = { 0.4f,0.4f,0.4f,1.0f };

	FrameBuffer frameBuffer;
#pragma endregion

	while (!glfwWindowShouldClose(winManager.GetWindow()))
	{
		mainCamera.UpdateMatrix(45.0f, 0.1f, 1000.0f, shaderLibrary.GetShader("StandardShader"));
		winManager.OnUpdate();
		ui_interface.Begin();

		Blaze::UI::MainMenuBar(winManager);

		Blaze::UI::LightingPanel(shaderLibrary.GetShader("StandardShader"), ambientColor);

		Blaze::UI::ViewportPanel(frameBuffer, winManager);

		Blaze::UI::HierarchyPanel(mainScene);

		Blaze::UI::PropertyPanel(mainScene, shaderLibrary.GetShader("StandardShader"), winManager.GetWindow());

		Blaze::UI::ProfilerPanel(winManager);

		Blaze::UI::ShaderLibPanel(shaderLibrary);

#pragma region Rendering
		frameBuffer.Bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.16f, 0.16f, 0.125f, 1.0f);
		texture.Bind();
		mainScene.m_Registry.each([&](entt::entity entity)
			{
				mainScene.m_Registry.get<Renderer>(entity).model.Draw(shaderLibrary.GetShader("StandardShader"));
			});
		frameBuffer.UnBind();
#pragma endregion 

		ui_interface.End();
		mainCamera.Input(winManager.GetWindow());
		winManager.OnUpdateComplete();
	}
#pragma region CleanUp
	ui_interface.OnDetach();
	winManager.OnDetach();
	return EXIT_SUCCESS;
#pragma endregion
}
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
#include"Renderer/ShaderLibrary.h"
#include"Renderer/Rendering.h"

#include"Windows/FileDialog.h"
#include"Windows/Prompt.h"

#include"Benchmark/Timer.h"
#include"Benchmark/Logger.h"

#include"Core/WindowManager.h"
#include"UI/CoreUI.h"
#include"UI/Panel.h"

int main(int args, char** argv)
{
#pragma region Setup
	WindowManager winManager;
	winManager.OnAttach();
	CoreUI ui_interface;
	ui_interface.OnAttach(winManager.GetWindow());
#pragma endregion 

#pragma region Initilization
	Camera mainCamera(winManager.width, winManager.height, glm::vec3{ 5.0f, 5.0f, -15.0f });
	ShaderLibrary shaderLibrary;
	Scene mainScene(shaderLibrary);
	shaderLibrary.AddShader("StandardShader", "Shader\\standard.vert", "Shader\\standard.frag");
	shaderLibrary.AddShader("LightShader", "Shader\\standard.vert", "Shader\\Light.frag");
	Blaze::Rendering renderer;
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

		texture.Bind();
		renderer.Draw(mainScene, shaderLibrary.GetShader("StandardShader"), frameBuffer);

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
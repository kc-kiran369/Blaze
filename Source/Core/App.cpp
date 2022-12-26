#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

#include"stb_image/stb_image.h"
#include"Core/App.h"

Application::Application(const char* AppName, int width, int height)
{
	m_Window = std::make_unique<WindowManager>(AppName, width, height);
	m_Window->OnAttach();
	m_UI = std::make_unique<CoreUI>(m_Window->GetWindow());
	m_UI->OnAttach();
}

void Application::Run()
{

	Camera mainCamera(m_Window->GetWidth(), m_Window->GetHeight(), glm::vec3{ 5.0f, 5.0f, -15.0f });
	ShaderLibrary shaderLibrary;
	Scene mainScene(shaderLibrary);
	shaderLibrary.AddShader("StandardShader", "Shader\\standard.vert", "Shader\\standard.frag");
	shaderLibrary.AddShader("LightShader", "Shader\\standard.vert", "Shader\\Light.frag");
	Blaze::Rendering renderer;
	Texture texture("Resources\\Images\\MedievalhouseDiffuse.jpg", 0);
	float ambientColor[] = { 0.4f,0.4f,0.4f,1.0f };
	FrameBuffer frameBuffer;

	while (!glfwWindowShouldClose(m_Window->GetWindow()))
	{
		mainCamera.UpdateMatrix(45.0f, 0.1f, 1000.0f, shaderLibrary.GetShader("StandardShader"));

		m_Window->OnUpdate();

		m_UI->Begin();

		Blaze::UI::MainMenuBar(*m_Window.get());
		Blaze::UI::LightingPanel(shaderLibrary.GetShader("StandardShader"), ambientColor);
		Blaze::UI::ViewportPanel(frameBuffer, *m_Window.get());
		Blaze::UI::HierarchyPanel(mainScene);
		Blaze::UI::PropertyPanel(mainScene, shaderLibrary.GetShader("StandardShader"), m_Window->GetWindow());
		//Blaze::UI::ProfilerPanel(winManager);
		Blaze::UI::ShaderLibPanel(shaderLibrary);

		texture.Bind();
		renderer.Draw(mainScene, shaderLibrary.GetShader("StandardShader"), frameBuffer);

		m_UI->End();
		mainCamera.Input(m_Window->GetWindow());
		m_Window->OnUpdateComplete();
	}

	m_UI->OnDetach();
	m_Window->OnDetach();
}
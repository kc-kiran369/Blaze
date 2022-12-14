#include"Core/WindowManager.h"

WindowManager::WindowManager(const char* name, uint16_t width, uint16_t height)
{
	glfwInit();
	m_Window = glfwCreateWindow(width, height, name, nullptr, nullptr);
	if (m_Window)
		Logger::Info("Window initialized");
	else
		Logger::Error("Window didn't create");
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

WindowManager::~WindowManager()
{
	Logger::Info("Window Manager Out Of Scope...");
}

void WindowManager::OnAttach()
{
	this->SetIcon();
	glfwMakeContextCurrent(m_Window);
	glfwSwapInterval(1);
	glewInit();

#ifdef DEBUG_BUILD
	Logger::Info("DEBUG BUILD");
#elif RELEASE_BUILD
	Logger::Info("RELEASE BUILD");
#endif

	Logger::Info("Manufacturer : %s", glGetString(GL_RENDERER));
	Logger::Info("Vendor : %s", glGetString(GL_VENDOR));
	Logger::Info("Version : %s", glGetString(GL_VERSION));
	Logger::Info("GLSL Version : %s\n", glGetString(0x8B8C));

	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
}

void WindowManager::OnDetach()
{
	glfwTerminate();
}

void WindowManager::OnUpdate()
{
	m_CurrTime = glfwGetTime();
	m_TimeDiff = m_CurrTime - m_PreTime;
}

void WindowManager::OnUpdateComplete()
{
	glfwPollEvents();
	glfwSwapBuffers(m_Window);
	m_PreTime = m_CurrTime;
}

float WindowManager::deltaTime()
{
	return (1 / m_TimeDiff);
}

float WindowManager::LastFrameTime()
{
	return  m_TimeDiff;
}

GLFWwindow* WindowManager::GetWindow()
{
	return m_Window;
}

void WindowManager::SetIcon()
{
	/*glfwimage images;
	images.pixels = stbi_load("resources\\icon\\logo_001.png", &images.width, &images.height, 0, 4);
	glfwsetwindowicon(m_window, 1, &images);
	stbi_image_free(images.pixels);*/
}

void WindowManager::ToggleSystemConsole()
{
	ShowWindow(GetConsoleWindow(), (IsWindowVisible(GetConsoleWindow()) ? SW_HIDE : SW_SHOW));
}

uint32_t WindowManager::GetWidth()
{
	return m_Width;
}

uint32_t WindowManager::GetHeight()
{
	return m_Height;
}

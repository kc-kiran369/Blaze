#ifndef APP_H
#define APP_H


#include"Core/WindowManager.h"
#include"Renderer/Texture.h"

#include"ECS/Entity.h"
#include"ECS/Scene.h"
#include"ECS/Component/Components.h"
#include"Renderer/Camera.h"
#include"Renderer/FrameBuffer.h"
#include"Renderer/Shader.h"
#include"Renderer/model.h"
#include"Renderer/ShaderLibrary.h"
#include"Renderer/Rendering.h"

#include"UI/CoreUI.h"
#include"UI/Panel.h"

class Application
{
private:
	std::unique_ptr<WindowManager> m_Window;
	std::unique_ptr<CoreUI> m_UI;
public:
	Application(const char* AppName, int width, int height);
	void Run();
};

#endif // !APP_H
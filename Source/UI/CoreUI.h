#ifndef COREUI_H
#define COREUI_H

#include"ImGUI/imgui.h"
#include"ImGUI/imgui_impl_glfw.h"
#include"ImGUI/imgui_impl_opengl3.h"

class CoreUI
{
public:
	CoreUI() = default;
	~CoreUI() = default;

	void OnAttach(GLFWwindow* window);
	void OnDetach();

	void Begin();
	void End();

	void SetDarkThemeColors();
private:
	ImGuiIO* io;
	ImGuiStyle* style;
	ImVec4* colors;
};
#endif
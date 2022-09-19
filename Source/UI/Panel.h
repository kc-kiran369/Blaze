#ifndef PANEL_H
#define PANEL_H

#include"../Renderer/FrameBuffer.h"
#include"../Core/WindowManager.h"
#include"imgui/imgui.h"
#include"../Windows/Prompt.h"

#include"glm/glm.hpp"
#include <imgui/imgui_internal.h>

#include"../ECS/Scene.h"
#include"../ECS/Entity.h"

#include"../ECS/Component/Components.h"

#include"../Renderer/Shader.h"

#include"../Windows/FileDialog.h"

#include"../Renderer/ShaderLibrary.h"

#include"../Math/Mathf.h"

#define NO_ENTITY -1

namespace Blaze
{
	namespace UI
	{
		bool DrawVec3Control(const char* label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f);

		void MainMenuBar(WindowManager& window);
		void ViewportPanel(FrameBuffer& frameBuffer, WindowManager& winManager);
		void HierarchyPanel(Scene& scene);
		void PropertyPanel(Scene& scene, Shader& shader, GLFWwindow* window);
		void ProfilerPanel(WindowManager& winManager);
		void LightingPanel(Shader& shader, float ambientColor[4]);
		void ShaderLibPanel(ShaderLibrary& lib);
	}
}
#endif                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
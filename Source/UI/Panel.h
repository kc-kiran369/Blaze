#ifndef PANEL_H
#define PANEL_H

#include"../Core/WindowManager.h"
#include"imgui/imgui.h"
#include"../Windows/Prompt.h"

#include"glm/glm.hpp"
#include <imgui/imgui_internal.h>

bool DrawVec3Control(const char* label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f);

void MainMenuBar(WindowManager& window);

#endif                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   

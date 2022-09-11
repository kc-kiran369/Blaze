#include"UI/Panel.h"

bool DrawVec3Control(const char* label, glm::vec3& values, float resetValue, float columnWidth)
{
	bool valueChanged = false;
	ImGuiIO& io = ImGui::GetIO();
	auto boldFont = io.Fonts->Fonts[0];

	ImGui::PushID(label);

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, columnWidth);
	ImGui::Text("%s", label);
	ImGui::NextColumn();

	ImGuiStyle& style = ImGui::GetStyle();

	ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

	float lineHeight = ImGui::GetFontSize() + style.FramePadding.y * 2.0f;
	ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
	ImGui::PushFont(boldFont);
	if (ImGui::Button("X", buttonSize))
		values.x = resetValue;
	ImGui::PopFont();
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	if (ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f"))
		valueChanged = true;
	ImGui::PopItemWidth();
	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
	ImGui::PushFont(boldFont);
	if (ImGui::Button("Y", buttonSize))
		values.y = resetValue;
	ImGui::PopFont();
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	if (ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f"))
		valueChanged = true;
	ImGui::PopItemWidth();
	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
	ImGui::PushFont(boldFont);
	if (ImGui::Button("Z", buttonSize))
		values.z = resetValue;
	ImGui::PopFont();
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	if (ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f"))
		valueChanged = true;
	ImGui::PopItemWidth();

	ImGui::PopStyleVar();

	ImGui::Columns(1);

	ImGui::PopID();
	return valueChanged;
}



void MainMenuBar(WindowManager& window)
{
#pragma region MainMenuBar
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("Open", "Ctrl+O");
			ImGui::MenuItem("New", "Ctrl+N");
			ImGui::MenuItem("Save as", "Ctrl+S");
			if (ImGui::MenuItem("Exit", "Ctrl+Q"))
			{
				if (Prompt::Open(window.GetWindow(), "Any unsaved progress will be lost", "Are you sure want to exit!!", MB_YESNO | MB_ICONINFORMATION) == IDYES)
				{
					glfwSetWindowShouldClose(window.GetWindow(), 1);
				}
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Preferences"))
			{

			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("View"))
		{
			ImGui::MenuItem("Hide All Panels");
			ImGui::MenuItem("Property Panel");
			ImGui::MenuItem("Grid");
			ImGui::MenuItem("Zoom in  -");
			ImGui::MenuItem("Zoom out +");
			ImGui::MenuItem("Reset Camera +");
			if (ImGui::MenuItem("Toggle System Terminal"))
			{
				window.ToggleSystemConsole();
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Add"))
		{
			if (ImGui::MenuItem("Empty Entity"))
			{

			}
			ImGui::MenuItem("Cone");
			ImGui::MenuItem("Cylinder");
			ImGui::MenuItem("Sphere");
			if (ImGui::MenuItem("Import Model.."))
			{
				/*std::string path = FileDialog::OpenFile("*.fbx\0", window.GetWindow());
				model.loadModel(path);*/
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
#pragma endregion
}

//void LightningPanel()
//{
//	ImGui::Begin("Lightning");
//	if (ImGui::TreeNode("Basic")) {
//		if (ImGui::ColorEdit4("Ambient Color", ambientColor, ImGuiColorEditFlags_NoInputs))
//		{
//			standardShader.SetVec4("_ambientColor", ambientColor[0], ambientColor[1], ambientColor[2], ambientColor[3]);
//		}
//		ImGui::TreePop();
//	}
//	ImGui::End();
//}
//
//void ViewportPanel()
//{
//	ImGui::Begin("Viewport", (bool*)0, ImGuiWindowFlags_NoResize);
//	ImGui::Image((ImTextureID)framerBuffer.GetColorTexture(), ImVec2{ 1000,1000 });
//	ImGui::End();
//}
//
//void HierarchyPanel()
//{
//	ImGui::Begin("Camera Settings");
//	ImGui::SliderFloat("Sensitivity", &mainCamera.sensitivity, 20.0f, 50.0f, "%.3f", 1.0f);
//	ImGui::SliderFloat("Speed", &mainCamera.speed, 0.01f, 1.0f, "%.3f", 1.0f);
//	ImGui::End();
//
//	ImGui::Begin("Hierarchy");
//	ImGui::Text("Total entities : %d", mainScene.m_Registry.size());
//	for (auto entity : view)
//	{
//		if (ImGui::MenuItem(view.get<Tag>(entity).tag.c_str(), (const char*)0, (activeEnt ? (activeEnt->GetComponent<Tag>().tag == view.get<Tag>(entity).tag ? true : false) : false), true))
//		{
//			activeEnt->m_Entity = entity;
//		}
//	}
//
//	if (ImGui::BeginPopupContextWindow(0, ImGuiMouseButton_Right, false))
//	{
//		if (ImGui::MenuItem("Empty Entity"))
//		{
//			Entity* temp = mainScene.CreateEntity();
//			if (mainScene.m_Registry.size() == 1)
//				activeEnt = temp;
//		}
//		if (ImGui::MenuItem("Cube")) {}
//		if (ImGui::MenuItem("Cylinder")) {}
//		if (ImGui::MenuItem("Sphere")) {}
//		if (ImGui::MenuItem("Cone")) {}
//		if (ImGui::MenuItem("Import..")) {}
//		ImGui::EndPopup();
//	}
//	ImGui::End();
//}
//
//void EntityDebuggerPanel()
//{
//	ImGui::Begin("Entity Debugger");
//	if (activeEnt)
//	{
//		ImGui::Text("Entity ID : %d", activeEnt->m_Entity);
//		ImGui::Text("Entity Name : %s", activeEnt->GetComponent<Tag>().tag.c_str());
//	}
//	ImGui::End();
//}
//
//void Profiler()
//{
//	ImGui::Begin("Profiler");
//	ImGui::Text("FPS : %f", winManager.deltaTime());
//	ImGui::Text("Last Render Time : %dms", 0.0f);
//	ImGui::End();
//}
//
//void PropertyPanel()
//{
//	ImGui::Begin("Property");
//	if (activeEnt)
//	{
//		ImGui::Text(activeEnt->GetComponent<Tag>().tag.c_str());
//
//		if (ImGui::IsItemDeactivatedAfterEdit())
//			Logger::Error("Deactivated");
//
//		/*if (ImGui::InputText("Rename", name, sizeof(name)))
//		{
//			if (name[0] != '\0' || name[0] != 0)
//			{
//				activeEnt->GetComponent<Tag>().tag = name;
//			}
//			else
//			{
//				Logger::Warn("Name is empty");
//			}
//		}*/
//
//		if (!activeEnt->HasComponent<Transform>())
//			ImGui::Text("No Transform Component");
//		else
//		{
//			ImGui::BeginGroup();
//			ImGui::Columns(2, 0, false);
//			ImGui::Text("Transform");
//			ImGui::NextColumn();
//			/*if (ImGui::Button("X"))
//			{
//
//			}*/
//			ImGui::Columns(1);
//
//			glm::vec3 temp = glm::vec3(0);
//			if (ImGui::SliderFloat("x", &temp.x, -10.0f, 10.0f, "%.3f", 1.0f))
//			{
//				activeEnt->GetComponent<Transform>().transform = temp;
//				_model = glm::translate(_model, temp);
//			}
//			if (ImGui::SliderFloat("y", &temp.y, -100.0f, 100.0f, "%.3f", 1.0f))
//				activeEnt->GetComponent<Transform>().transform += temp;
//			if (ImGui::SliderFloat("z", &temp.z, -100.0f, 100.0f, "%.3f", 1.0f))
//				activeEnt->GetComponent<Transform>().transform += temp;
//			ImGui::EndGroup();
//		}
//
//		if (!activeEnt->HasComponent<Renderer>())
//			ImGui::Text("No Renderer Component");
//		else
//		{
//			ImGui::Text("Renderer");
//			if (ImGui::Button("Select Mesh"))
//			{
//				activeEnt->GetComponent<Renderer>().model.loadModel(FileDialog::OpenFile("*.fbx\0", winManager.GetWindow()));
//			}
//		}
//	}
//	ImGui::End();
//}

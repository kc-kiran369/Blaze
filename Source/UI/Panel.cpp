#include"UI/Panel.h"

namespace Blaze
{
	namespace UI
	{
		Entity* activeEntity = nullptr;
		entt::entity SelectedEntity = entt::entity(NO_ENTITY);

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
			{
				values.x = resetValue;
				valueChanged = true;
			}
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
			{
				values.y = resetValue;
				valueChanged = true;
			}
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
			{
				values.z = resetValue;
				valueChanged = true;
			}
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
				ImGui::EndMainMenuBar();
			}
		}


		void LightingPanel(Shader& shader, float ambientColor[4])
		{
			ImGui::Begin("Lightning");
			if (ImGui::TreeNodeEx("Basic", ImGuiTreeNodeFlags_DefaultOpen)) {
				if (ImGui::ColorEdit4("Ambient Color", ambientColor, ImGuiColorEditFlags_NoInputs))
				{
					shader.SetVec4("_ambientColor", ambientColor[0], ambientColor[1], ambientColor[2], ambientColor[3]);
				}
				ImGui::TreePop();
			}
			ImGui::End();
		}


		void ViewportPanel(FrameBuffer& frameBuffer, WindowManager& winManager)
		{
			ImGui::Begin("Viewport", (bool*)0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_MenuBar);
			ImGui::BeginMenuBar();
			ImGui::Text("%f", winManager.deltaTime());
			ImGui::EndMenuBar();
			ImGui::Image((ImTextureID)frameBuffer.GetColorTexture(), ImVec2{ Blaze::Math::Mathf::max<float>(720.0f,(float)ImGui::GetWindowWidth()),(float)ImGui::GetWindowWidth() / 1.7778f });
			ImGui::End();
		}


		void HierarchyPanel(Scene& scene)
		{
			ImGui::Begin("Hierarchy");
			ImGui::Text("Total entities : %d", scene.m_Registry.size());
			if (ImGui::BeginPopupContextWindow("AddMenu", ImGuiMouseButton_Right, false))
			{
				if (ImGui::MenuItem("Empty Entity"))
				{
					Entity* temp = scene.CreateEntity();
				}
				if (ImGui::MenuItem("Light"))
				{
					Entity* temp = scene.CreateEntity();
					temp->AddComponent<Light>();
				}
				ImGui::EndPopup();
			}

			if (ImGui::TreeNodeEx("Scene", ImGuiTreeNodeFlags_DefaultOpen))
			{
				scene.m_Registry.each([&](entt::entity entity)
					{
						if (ImGui::MenuItem(scene.m_Registry.get<Tag>(entity).tag.c_str(), (const char*)0, SelectedEntity == entity, true))
						{
							if (SelectedEntity != entity)
								SelectedEntity = entity;
							else if (SelectedEntity == entity)
								SelectedEntity = entt::entity(NO_ENTITY);
						}
					});
				ImGui::TreePop();
			}
			ImGui::End();
		}


		void ProfilerPanel(WindowManager& winManager)
		{
			ImGui::Begin("Profiler");
			/*ImGui::Text("FPS : %f", winManager.deltaTime());
			ImGui::Text("Last Frame : %f", winManager.LastFrameTime());*/
			ImGui::End();
		}


		void PropertyPanel(Scene& scene, Shader& shader, GLFWwindow* window)
		{
			for (auto entity : scene.entities)
			{
				if (entity->m_Entity == SelectedEntity)
					activeEntity = entity;
			}
			ImGui::Begin("Property");
			if (activeEntity)
			{
				ImGui::Text(activeEntity->GetComponent<Tag>().tag.c_str());
				ImGui::Separator();

				if (ImGui::TreeNodeEx("Transform", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_Selected))
				{
					if (!activeEntity->HasComponent<Transform>())
						ImGui::Text("No Transform Component");
					else
					{
						if (Blaze::UI::DrawVec3Control("Translation", activeEntity->GetComponent<Transform>().transform, 0.0f, 100.0f))
						{
							activeEntity->GetComponent<Transform>().OnTransformChange(shader);
						}

						if (Blaze::UI::DrawVec3Control("Rotation", activeEntity->GetComponent<Transform>().rotation, 0.0f, 100.0f))
						{
							auto& mat = activeEntity->GetComponent<Transform>().modelMatrix;
							mat = glm::rotate(mat, glm::radians(1.0f), activeEntity->GetComponent<Transform>().rotation);
							activeEntity->GetComponent<Transform>().OnTransformChange(shader);
						}

						Blaze::UI::DrawVec3Control("Scale", activeEntity->GetComponent<Transform>().scale, 1.0f, 100.0f);

						ImGui::Separator();
					}
					ImGui::TreePop();
				}

				if (ImGui::TreeNodeEx("Renderer", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_Selected))
				{
					if (!activeEntity->HasComponent<Renderer>())
					{
						ImGui::Text("No Renderer Component");
					}
					else
					{
						if (activeEntity->GetComponent<Renderer>().hasModel)
						{
							ImGui::Text("It already has model");
						}
						else
						{
							if (ImGui::Button("Select Mesh"))
							{
								activeEntity->GetComponent<Renderer>().model.loadModel(FileDialog::OpenFile("*.fbx\0", window));
								activeEntity->GetComponent<Renderer>().hasModel = true;
							}
							ImGui::Separator();
						}
						if (activeEntity->HasComponent<Material>())
						{
							if (ImGui::TreeNodeEx("Material", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding))
							{
								ImGui::Text("Shader Type : Standard Shader");
								if (ImGui::ColorEdit4("Albedo", &activeEntity->GetComponent<Material>().m_Albedo.x, ImGuiColorEditFlags_NoInputs))
								{
									activeEntity->GetComponent<Material>().UploadToShader();
								}
								ImGui::SliderFloat("Metallic", &activeEntity->GetComponent<Material>().m_Metallic, 0.0f, 1.0f, "%.3f", 1.0f);
								ImGui::SliderFloat("Smoothness", &activeEntity->GetComponent<Material>().m_Smoothness, 0.0f, 1.0f, "%.3f", 1.0f);
								ImGui::TreePop();
							}
							ImGui::Separator();
						}
					}
					ImGui::TreePop();
				}



				if (activeEntity->HasComponent<Light>())
				{
					if (ImGui::TreeNodeEx("Light", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_Selected))
					{
						ImGui::SliderFloat("Intensity", &activeEntity->GetComponent<Light>().intensity, 0.0f, 50.0f, "%.2f", 1.0f);
						ImGui::ColorEdit3("Color", &activeEntity->GetComponent<Light>().color.x);
						ImGui::Separator();
						ImGui::TreePop();
					}
				}

				if (ImGui::Button("Add Component", ImVec2{ ImGui::GetWindowWidth(),30 }))
				{
					ImGui::OpenPopup("AddComp");
				}

				if (ImGui::BeginPopup("AddComp"))
				{
					ImGui::MenuItem("Rigidbody");
					ImGui::MenuItem("Light");
					ImGui::EndPopup();
				}

				if (ImGui::Button("Delete Entity", ImVec2{ ImGui::GetWindowWidth(),25.0f }))
				{
					/*activeEntity->DeleteEntity();*/
				}
			}
			ImGui::End();
		}


		void ShaderLibPanel(ShaderLibrary& lib)
		{
			ImGui::Begin("Shader Library");
			ImGui::Text("%d", lib.GetCount());
			ImGui::End();
		}
	}
}
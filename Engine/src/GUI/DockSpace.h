#pragma once
#include "Window/Window.h"
#include "imgui.h"
#include "ImGuiThemes.h"

namespace Engine {

	class Dockspace {
	public:
		static void begin(Window& window) {
			// Note: Switch this to true to enable dockspace
			static bool dockspaceOpen = true;
			static bool opt_fullscreen_persistant = true;
			bool opt_fullscreen = opt_fullscreen_persistant;
			static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

			// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
			// because it would be confusing to have two docking targets within each others.
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
			if (opt_fullscreen)
			{
				ImGuiViewport* viewport = ImGui::GetMainViewport();
				ImGui::SetNextWindowPos(viewport->Pos);
				ImGui::SetNextWindowSize(viewport->Size);
				ImGui::SetNextWindowViewport(viewport->ID);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
				window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
				window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
			}

			// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
			if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
				window_flags |= ImGuiWindowFlags_NoBackground;

			// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
			// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
			// all active windows docked into it will lose their parent and become undocked.
			// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
			// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
			ImGui::PopStyleVar();

			if (opt_fullscreen)
				ImGui::PopStyleVar(2);

			// DockSpace
			ImGuiIO& io = ImGui::GetIO();
			ImGuiStyle& style = ImGui::GetStyle();
			float minWinSizeX = style.WindowMinSize.x;
			style.WindowMinSize.x = window.getWindowProperties().height / 4.0f;
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			}

			style.WindowMinSize.x = minWinSizeX;

			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("Menu"))
				{

					ImGui::EndMenu();
				}

				if (ImGui::BeginMenu("Themes")) {
					ImGuiStyle& style = ImGui::GetStyle();

					if (ImGui::MenuItem("Dark theme 1")) {
						ImGuiThemes::DarkTheme1(style);
					}

					if (ImGui::MenuItem("Dark theme 2")) {
						ImGuiThemes::DarkTheme2(style);
					}

					if (ImGui::MenuItem("Light theme 1")) {
						ImGuiThemes::LightTheme1(style);
					}

					if (ImGui::MenuItem("Light theme 2")) {
						ImGuiThemes::LightTheme2(style);
					}

					ImGui::EndMenu();
				}

				ImGui::EndMenuBar();

				/*ImGui::Begin("Colors");
				ImGuiStyle *ref = &(ImGui::GetStyle());

				static ImGuiTextFilter filter;
				filter.Draw("Filter colors", ImGui::GetFontSize() * 16);

				static ImGuiColorEditFlags alpha_flags = 0;
				if (ImGui::RadioButton("Opaque", alpha_flags == ImGuiColorEditFlags_None)) { alpha_flags = ImGuiColorEditFlags_None; } ImGui::SameLine();
				if (ImGui::RadioButton("Alpha", alpha_flags == ImGuiColorEditFlags_AlphaPreview)) { alpha_flags = ImGuiColorEditFlags_AlphaPreview; } ImGui::SameLine();
				if (ImGui::RadioButton("Both", alpha_flags == ImGuiColorEditFlags_AlphaPreviewHalf)) { alpha_flags = ImGuiColorEditFlags_AlphaPreviewHalf; } ImGui::SameLine();

				for (int i = 0; i < ImGuiCol_COUNT; i++)
				{
					const char* name = ImGui::GetStyleColorName(i);
					if (!filter.PassFilter(name))
						continue;
					ImGui::PushID(i);
					ImGui::ColorEdit4("##color", (float*)&style.Colors[i], ImGuiColorEditFlags_AlphaBar | alpha_flags);
					if (memcmp(&style.Colors[i], &ref->Colors[i], sizeof(ImVec4)) != 0)
					{
						// Tips: in a real user application, you may want to merge and use an icon font into the main font,
						// so instead of "Save"/"Revert" you'd use icons!
						// Read the FAQ and docs/FONTS.md about using icon fonts. It's really easy and super convenient!
						ImGui::SameLine(0.0f, style.ItemInnerSpacing.x); if (ImGui::Button("Save")) { ref->Colors[i] = style.Colors[i]; }
						ImGui::SameLine(0.0f, style.ItemInnerSpacing.x); if (ImGui::Button("Revert")) { style.Colors[i] = ref->Colors[i]; }
					}
					ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
					ImGui::TextUnformatted(name);
					ImGui::PopID();
				}
				ImGui::End();*/
			}
		}

		static void end() {
			ImGui::End();
		}
	};
}
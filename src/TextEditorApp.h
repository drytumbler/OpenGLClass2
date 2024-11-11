// TextEditorApp.h

#pragma once

#include <deque>
#include <iostream>
#include <unordered_set>
#include "imgui/imgui.h"
#include "config.h"
#include "TextEditorBuffer.h"

// #include <algorithm>

struct MyColors {
  ImU32 DefaultButtonColor;
  ImU32 HoveredButtonColor;
  ImU32 ActiveButtonColor;
  MyColors(){  }
  void SetColorsToDefault(){
    if(ImGui::GetCurrentContext() == nullptr) return;
    // ImGui Context must be available before we can acces these built-in colors
    ImVec4 defaultButtonColor = ImGui::GetStyleColorVec4(ImGuiCol_WindowBg);
    ImVec4 hoveredButtonColor = ImGui::GetStyleColorVec4(ImGuiCol_Tab);
    ImVec4 activeButtonColor = ImGui::GetStyleColorVec4(ImGuiCol_ButtonActive);

    DefaultButtonColor = ImGui::ColorConvertFloat4ToU32(defaultButtonColor);
    HoveredButtonColor = ImGui::ColorConvertFloat4ToU32(hoveredButtonColor);
    ActiveButtonColor = ImGui::ColorConvertFloat4ToU32(activeButtonColor);

  }
};

struct TextEditorApp
{
  ImVector<TextEditorBuffer>    Documents;
  ImVector<TextEditorBuffer*>   CloseQueue;
  TextEditorBuffer*             RenamingDoc = NULL;
  bool                          RenamingStarted = false;
  bool ShowBufferList = true;
  MyColors Colors;
  std::string loadPath = expandHome(DEFAULT_LOAD_PATH);
    
  TextEditorApp();
  void DisplayMenuBar();
  void GetTabName(TextEditorBuffer* doc, char* out_buf, size_t out_buf_size);
  void DisplayDocContents(TextEditorBuffer* doc);
  void DisplayDocContextMenu(TextEditorBuffer* doc);
  void NotifyOfDocumentsClosedElsewhere();
  int  RequestDocumentID();
  void Show();
  void OpenDocument();
  void AppendToRecentDocuments(const char* text);
  bool CustomButton(const char* label, const ImVec2& size, ImU32 textcolor = IM_COL32(255,255,255,255));
public:
  bool Visible = true;  
  static ImFont* CodeFont;
  static void LoadFonts();
};


// TextEditorApp.h

#pragma once

#include <deque>
#include <iostream>
#include <unordered_set>
#include "imgui/imgui.h"
#include "config.h"
#include "TextEditorBuffer.h"
#include "Shader.h"
#include "State.h"


// #include <algorithm>

struct MyColors {
  ImU32 DefaultButtonColor = IM_COL32(255, 255, 255, 255);
  ImU32 HoveredButtonColor = IM_COL32(255, 255, 255, 255);
  ImU32 ActiveButtonColor = IM_COL32(255, 255, 255, 255);
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
  std::string loadPath = expandHome(DEFAULT_LOAD_PATH);
    
  TextEditorApp();
  void DisplayMenuBar(int open_count);
  void GetTabName(TextEditorBuffer* doc, char* out_buf, size_t out_buf_size);
  void DisplayDocContents(TextEditorBuffer* doc);
  void DisplayDocContextMenu(TextEditorBuffer* doc);
  void NotifyOfDocumentsClosedElsewhere();
  int  RequestDocumentID();
  void Show(ImVec2 space);
  void OpenDocument();
  void AppendToRecentDocuments(const char* text);
public:
  MyColors Colors;
  bool Visible = true;  
  static ImFont* CodeFont;
  static void LoadFonts();
};



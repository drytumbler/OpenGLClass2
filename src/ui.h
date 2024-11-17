// ui.h
#pragma once
#include <cstddef>
#define UI_MAIN_BAR_MENU_1 "Menu"
#include "config.h"
#include "nfd/nfd.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "TextEditorApp.h"
#include "TextEditorBuffer.h"
#include "TextureBrowser.h"
#define assertm(exp, msg) assert(((void)msg, exp))

class ui{
private:
  GLFWwindow* Window;
  bool SetupDone = false;
  bool ASSERT(bool* check);
  bool uiOn = true; // used in key_callback() function to disable UI at runtime
public:
  static void Refresh(){ EditorReady = false; TexterReady = false; };
  static bool EditorReady;
  static bool TexterReady;
  static std::filesystem::path BrowserPath;
  static TextEditorApp Editor;
  static TextureBrowser Texter;
  bool uiHovered = false;
  bool uiRequestExit =
    false; // used to request exit from the ImGui::MainMenuBar()
  //bool showEditor = true;
  ui(){ }
  ui(GLFWwindow* window){
    Window = window;
    Setup();
  }
  void Setup();
  void Run();
  void Render();
  void Quit();
  void Toggle();
  void ShowMainFileMenu();
  void ShowTextEditorApp(ImVec2 space);
  void ShowTextureBrowser(ImVec2 space);
  bool RunActivityCheck();
  
  bool GetSetupDone(){ return SetupDone; }
  bool GetuiOn(){ return uiOn; }
  bool GetuiHovered(){ return RunActivityCheck(); }

  GLFWwindow* GetWindow() { return Window; }

  static std::filesystem::path GetBrowserPath() {
    printf("current path: %s\n", BrowserPath.c_str());
    return ui::BrowserPath;
  }
  static void SetBrowserPath(std::filesystem::path path) {
    if(path == BrowserPath) return;
    ui::BrowserPath = path;
    printf("path set to: %s\n", BrowserPath.c_str());
    ui::Refresh();
  }
  
  void SetWindow(GLFWwindow* window) { Window = window; }
  void SetuiOn(bool value) { uiOn = value; }
  void SetuiHovered(bool value) { uiHovered = value; }
};

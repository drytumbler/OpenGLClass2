// ui.h

#include <cstddef>
#define UI_MAIN_BAR_MENU_1 "Menu"
#include "config.h"
#include "nfd/nfd.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "TextEditorApp.h"
#include "TextEditorBuffer.h"

#define assertm(exp, msg) assert(((void)msg, exp))

class ui{
private:
  GLFWwindow* Window;
  bool SetupDone = false;
  bool ASSERT(bool* check);
  bool uiOn = true; // used in key_callback() function to disable UI at runtime
public:
  TextEditorApp Editor;
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
  void ShowTextEditorApp();
  bool RunActivityCheck();
  
  bool GetSetupDone(){ return SetupDone; }
  bool GetuiOn(){ return uiOn; }
  bool GetuiHovered(){ return RunActivityCheck(); }
  
  void SetWindow(GLFWwindow* window) { Window = window; }
  void SetuiOn(bool value) { uiOn = value; }
  void SetuiHovered(bool value) { uiHovered = value; }
};

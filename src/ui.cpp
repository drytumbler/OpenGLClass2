// ui.cpp


#include "ui.h"

void ui::Toggle() {
  uiOn = !uiOn;
}

void ui::Setup() {
    // Setup Dear ImGui context
  assert(Window && "UI_ERROR: No Valid GLFWwindow*");
  const char* glsl_version = "#version 130";
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
  
  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  //ImGui::StyleColorsLight();
  
  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(Window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  ImFont* RobotoFont = io.Fonts->AddFontFromFileTTF("../src/fonts/Roboto-Medium.ttf", 16);
  TextEditorApp::LoadFonts();
  //  ImGui_ImplOpenGL3_CreateFontsTexture();

  checkAndCreateFile(RECENT_DOCS_FILE);

  SetupDone = true;
}

void ui::Run() {
  ASSERT(&SetupDone);
  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();      

  ImGui::NewFrame();
  if(uiOn){
    if (ImGui::BeginMainMenuBar()){
      if (ImGui::BeginMenu(UI_MAIN_BAR_MENU_1)){
	ShowMainFileMenu();
	ImGui::EndMenu();
      }
      
      ImGui::EndMainMenuBar();
    }
    ShowTextEditorApp();
    uiHovered = ( ImGui::IsAnyItemHovered() || ImGui::IsAnyItemFocused() || ImGui::IsAnyItemActive() );
    uiHovered += ( ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) || ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow) );
  }
}

void ui::Render() {
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); // skip this to not render ui (eg. screenshot)
}

void ui::Quit() {
  // Terminate ImGui
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();  
}

void ui::ShowMainFileMenu(){
  // File menu of the MainMenuBar
  //Currently keypresses are handled by GLFW in the key_callback() function and the Camera class
  //IMGUI_DEMO_MARKER("Examples/Menu");
  //ImGui::MenuItem("(demo menu)", NULL, false, false);
  
  if (ImGui::MenuItem("New" , "Ctrl+N")){
    //createNewFile();
  }
  if (ImGui::MenuItem("Open", "Ctrl+O")) {
    // TODO
  }
  if (ImGui::BeginMenu("Open Recent")){
    if (ImGui::BeginMenu("More..")){
      ImGui::MenuItem("TO DO", NULL, false, false);
      ImGui::EndMenu();
    }
    ImGui::EndMenu();
  }
  if (ImGui::MenuItem("Save", "Ctrl+S")) {
    // TODO
  }
  if (ImGui::MenuItem("Save As..")) {
    // TODO
  }

  ImGui::Separator();
  if (ImGui::MenuItem("Editor...", "")) { Editor.Visible = !Editor.Visible; }
  ImGui::Separator();
  if (ImGui::MenuItem("Quit", "Alt+F4")) { uiRequestExit=true; }
}

void ui::ShowTextEditorApp(){
  if(Editor.Visible)
    Editor.Show();
}

bool ui::RunActivityCheck() {
  uiHovered = ( ImGui::IsAnyItemHovered() || ImGui::IsAnyItemFocused() || ImGui::IsAnyItemActive() );
  uiHovered += ( ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) || ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow) );
  return uiHovered;
}

bool ui::ASSERT(bool* check) {
  if(check == &SetupDone)
    assertm(*check, "UI_ERROR: Setup incomplete! Make sure 'ui::Window' is set before running 'ui::Setup()'");
  else assertm(*check, "UI_ERROR");
  return true;
}
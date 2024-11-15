// TextureBrowser.cpp

#include "TextureBrowser.h"
#include "imgui/imgui.h"
#include "State.h"
#include "ui.h"
#include <cstdio>
#include <filesystem>

void clearTextures();
void Warn();

void TextureBrowser::Display(ImVec2 space) {
    // Options
  float menuHeight = ImGui::GetFrameHeight();
  ImVec2 size = ImVec2(space.x * SIDEX, space.y); //space.y has menuHeight already deducted
  ImVec2 pos = ImVec2(space.x * MAINX, menuHeight);
  ImGui::SetNextWindowSize(size);
  ImGui::SetNextWindowPos(pos);
  
  static bool opt_reorderable = true;
  static ImGuiTabBarFlags opt_fitting_flags = ImGuiTabBarFlags_FittingPolicyDefault_;

  bool window_contents_visible = ImGui::Begin("Texture Browser", &Visible, ImGuiWindowFlags_MenuBar|ImGuiWindowFlags_NoScrollbar|ImGuiWindowFlags_NoScrollWithMouse);
  if (!window_contents_visible)
    {
      ImGui::End();
      return;
    }

  if(!State::GetInstance().GetTexturesLoaded() && ImGui::Button("LOAD")){
    // State::GetInstance().LoadTextures();
  }
  static Material Preview = Material(FOLDER_IMAGE);
  static int choice = 0;
  //  static std::filesystem::path dir{expandHome(TEXTURES)};
  static std::filesystem::path dir = ui::GetBrowserPath();
  static std::string begin = dir.filename();
  static std::string choice_t = begin.append("/");
  static std::vector<std::filesystem::path> dirs;
  static std::vector<std::filesystem::path> files;
  static std::string result;

  if(strcmp(dir.c_str(), result.c_str()) != 0) {
    ui::Refresh();
    choice_t = dir.filename();
    choice_t.append("/");
    result = dir;
  }

  //  if(ui::Refresh && strcmp(dir.c_str(), "") != 0){
  if(!ui::TexterReady){
    //result = dir;
    dir = ui::GetBrowserPath();
    if(dir.has_extension() &&
       (strcmp(dir.extension().c_str(), ".png") == 0) ||
       (strcmp(dir.extension().c_str(), ".jpg") == 0)
       ){
      Preview.Refresh(dir.c_str());
    }
    if (!dir.has_extension() && ((std::filesystem::directory_entry)dir).is_directory() && !dir.empty()){
      dirs.clear();
      files.clear();
      Preview.Refresh(FOLDER_IMAGE);
      for(auto const& dir_entry : std::filesystem::directory_iterator{dir}){
	if(dir_entry.is_directory())
	  dirs.push_back(dir_entry);
	else if(dir_entry.is_regular_file())
	  if(
	     (strcmp(dir_entry.path().extension().c_str(), ".png") == 0) ||
	     (strcmp(dir_entry.path().extension().c_str(), ".jpg") == 0)
	     )
	    files.push_back(dir_entry);
      }
    }
    ui::TexterReady = true;
  }
  
  if(ImGui::BeginCombo("#dir1", choice_t.c_str())){
    //ui::Refresh = true;
    char comp[64];
    snprintf(comp, sizeof(choice_t) + 6, "./ (%s)", choice_t.c_str());
    if(ImGui::Selectable(comp)) {
      choice = 0;
      choice_t = "./";
      ui::Refresh();
    }
    if(ImGui::Selectable("../ (up directory)")){
      choice = 0;
      if(dir.has_parent_path())
	{
	  ui::SetBrowserPath(dir.parent_path());
	  dir = dir.parent_path();
	}
      
      choice_t = dir.filename();
      choice_t += "/";
    }
    ImGui::Separator();

    int c = 3;
    if(!dirs.empty()){
      ImGui::PushStyleColor(0, IM_COL32(127,255,130,100));
      for (std::filesystem::path d : dirs){
	char name[64];
	strcpy(name, d.filename().c_str());
	name[strlen(d.filename().c_str())] = '/';
	name[strlen(d.filename().c_str()) + 1] = '\0';
	if(ImGui::Selectable(name)) {
	  choice = c;
	  choice_t = name;
	  
	}
	++c;
      }
      ImGui::PopStyleColor();
      ImGui::Separator();
      
    }
    if(!files.empty()){
      for (std::filesystem::path f : files){

        
	  char name2[64];
	  strcpy(name2, f.filename().c_str());
	  if(ImGui::Selectable(name2)){
	    choice = c;
	    choice_t = name2;
	  }
	  ++c;
	
      }
    }
    int n = 2 + dirs.size();
    
      result = (choice <= n) ? dir : files[choice - 1 - n]; // -1 because choice 0 does nothing
    
    if(choice > 2 && choice <= n){
      Warn();
      dir = dirs[choice - 1 - 2];
      printf("%s", dir.c_str());
      result = dir;
      choice = 0;
      ui::SetBrowserPath(dir);
    } else if (choice > n) {
      Preview.Refresh(result.c_str());
      choice = 0;
      ui::SetBrowserPath(result);
    }
    ImGui::EndCombo();
  }
  
  ImGui::Text(result.c_str());
  ImGui::BeginChild("upper", ImVec2(0, ImGui::GetContentRegionAvail().y / 2.));
  
  if (Preview.GetID()){
    //    float y = ImGui::GetContentRegionAvail().y; 
    ImVec2 image_size = ImVec2(size.x - 10, size.x - 10);
    ImGui::Image(Preview.GetID(), image_size, ImVec2(0, 1), ImVec2(1, 0));
    if(! ((std::filesystem::path)result).has_extension() ){
      ImVec2 text_size = ImGui::CalcTextSize(choice_t.c_str());
      ImGui::SetCursorPos(ImVec2( (size.x - text_size.x - 10) / 2., (size.x - text_size.y - 10) / 2. ));
      if(text_size.x < size.x - 20)
	ImGui::Text(choice_t.c_str());
    }
  }

  //  static std::filesystem::path selected;
  
  for(int i = 0; i < State::GetInstance().Materials.size(); i++){
    ImGui::PushID(i);
    GLuint textureID = State::GetInstance().Materials[i]->GetID();
    if(ImGui::ImageButton("##img", textureID, ImVec2(250., 250.), ImVec2(0, 1), ImVec2(1, 0))) puts("clicked");
    ImGui::PopID();
  }
  
  //ImGui::Image(State::GetInstance().Materials[i]->GetID(), ImVec2(50., 50.), ImVec2(0, 1), ImVec2(1, 0));
  ImGui::EndChild();
  ImGui::BeginChild("lower", ImVec2(0, ImGui::GetContentRegionAvail().y / 2.));
  ImGui::Text("down");
  if(ImGui::Button("Delete")) clearTextures();
  
  
  ImGui::EndChild();
  ImGui::End();
}

void clearTextures() {
  for (int i = 0; i < (int)State::GetInstance().Materials.size(); i++){
    //    State::GetInstance().Materials.erase(State::GetInstance().Materials.begin() + i);
    State::GetInstance().Materials.clear();
    
  }
}

void Warn() {
  static int n = 0;
  printf("%d", n++);
}

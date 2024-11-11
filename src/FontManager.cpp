// FontManager.cpp
#include "FontManager.h"

ImFont* FontManager::RobotoFont = nullptr;
ImFont *FontManager::CodeFont = nullptr;

void FontManager::LoadFonts(ImGuiIO& io){
    //io.Fonts->AddFontDefault();
    ImFont* RobotoFont = io.Fonts->AddFontFromFileTTF("../src/fonts/Roboto-Medium.ttf", 14);
    ImFont* CodeFont = io.Fonts->AddFontFromFileTTF("../src/fonts/SourceCodePro-Medium.ttf", 14);
    if (!RobotoFont || !CodeFont) {
      std::cout << "Failed to load fonts!" << std::endl;
    }
  }

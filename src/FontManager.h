#include "imgui/imgui.h"
#include <iostream>

class FontManager {
public:
  static ImFont* RobotoFont;  
  static ImFont* CodeFont;
  
  static void LoadFonts(ImGuiIO& io);
};

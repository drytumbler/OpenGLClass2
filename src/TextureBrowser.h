// TextureBrowser.h

#pragma once

#include "config.h"
#include "imgui/imgui.h"

#define FOLDER_IMAGE "../src/img/folder256_.png"

class TextureBrowser {
 public:
  bool Visible = true;
  void Display(ImVec2 space);
};

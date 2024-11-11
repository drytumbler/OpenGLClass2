// TextEditorBuffer.h
#pragma once

#ifndef TEXT_BUFFER_SIZE
#define TEXT_BUFFER_SIZE 8192
#endif

#ifndef DEFAULT_SAVE_PATH
#define DEFAULT_SAVE_PATH "~/projects/OpenGLClass2/src/shaders"
#endif


#include "config.h"
#include "imgui/imgui.h"

struct TextEditorBuffer
{
  char        Name[32];                  // The filename
  int         UID;                       // Unique ID (necessary as we can change title)
  bool        Open;                      // Set when open (we keep an array of all available documents to simplify demo code!)
  bool        OpenPrev;                  // Copy of Open from last update.
  bool        Dirty;                     // Set when the document has been modified
  bool        Popup;
  ImVec4      Color;                     // Arbitrary color variable for document
  char        Path[128];                 // The full path
  char        Data[TEXT_BUFFER_SIZE];    // Copy of the content

  // Constructor
  TextEditorBuffer(int uid, const char* name, const char* data, bool open = true, const char* path = "");
  
  // Document methods
  void DoOpen();
  void DoForceClose();
  int  DoSave();
  nfdresult_t DoRequestSaveLocation();
  void DoRefreshShader();
};

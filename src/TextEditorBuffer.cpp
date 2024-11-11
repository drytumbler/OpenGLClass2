// TextEditorBuffer.cpp

#include "TextEditorBuffer.h"

TextEditorBuffer::TextEditorBuffer(int uid, const char* name, const char* data, bool open, const char* path){
  UID = uid;
  snprintf(Name, sizeof(Name), "%s", name);
  Open = OpenPrev = open;
  Popup = true;
  Dirty = false;
  Color = ImVec4(1.0, 1.0, 1.0, 1.0);
  snprintf(Data, sizeof(Data), "%s", data);
  snprintf(Path, sizeof(Path), "%s", path);
}

void TextEditorBuffer::DoOpen()       { Open = true; }
void TextEditorBuffer::DoForceClose() { Open = false; Dirty = false; }  
int TextEditorBuffer::DoSave(){ // for now only works in same path
  std::string thePath = Path;
  if (thePath == "") {
    puts("no path");
    nfdresult_t result = DoRequestSaveLocation();
    if (result != NFD_OKAY) return -1;
  }
  std::filesystem::path saveLoc = constructFullPath(Path, Name);
  int result = checkAndCreateFile(saveLoc);
  std::string textdata;
  textdata = Data;
  textdata += '\n';
  
  switch (result){
  case -1: // error state
    std::cout << "File NOT saved." << std::endl;
    return -1;
    break;
  case 0: // empty file created
    saveToFile(saveLoc, textdata.c_str());
    std::cout << "File saved successfully." << std::endl;
    break;
  case 1: // file exists
    saveToFile(saveLoc, textdata.c_str());
    std::cout << "File saved successfully." << std::endl;
    break;
  }
  Dirty = false;
  return 0;
}
nfdresult_t TextEditorBuffer::DoRequestSaveLocation() {
  char* path;
  nfdresult_t result;
  result = NFD_SaveDialog(NULL, DEFAULT_SAVE_PATH, &path);
  
  if(result == NFD_OKAY){
    const char* name = strrchr(path, '/'); // actually the index of the last slash, hence name + 1
    if (!name) name = strrchr(path,'\\');
    if (name) name++;
    char location[128];
    strncpy(location, path, strlen(path) - strlen(name)); // copy last slash too
    location[strlen(path) - strlen(name)] = '\0'; // after last slash add null terminator
    
    strncpy(Path, location, sizeof(Path) - 1);
    strncpy(Name, name, sizeof(Name) - 1);
    //      puts(&Name[0]);
    //      puts(&Path[0]);
  }
  
  return result;
}

void TextEditorBuffer::DoRefreshShader() {
  
}

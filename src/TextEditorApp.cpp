// TextEditorApp.cpp

//-----------------------------------------------------------------------------
// [SECTION] Example App: Documents Handling / ShowTextEditorApp()
//-----------------------------------------------------------------------------

#include "TextEditorApp.h"
#include "imgui/imgui.h"
#include <vector>

ImFont* TextEditorApp::CodeFont = nullptr;

TextEditorApp::TextEditorApp(){
  Documents.push_back(TextEditorBuffer(0, "Empty Shader", "#version 330 core\n\nvoid main()\n{\n\n\tgl_FragColor = vec4( vec3( 0.0, 0.0, 0.0 ), 1.0 ); \n}\n", true));
}

void TextEditorApp::GetTabName(TextEditorBuffer* doc, char* out_buf, size_t out_buf_size){
  // As we allow to change document name, we append a never-changing document id so tabs are stable
  snprintf(out_buf, out_buf_size, "%s###doc%d", doc->Name, doc->UID);
}

void TextEditorApp::LoadFonts() {
  TextEditorApp::CodeFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("../src/fonts/SourceCodePro-Medium.ttf", 16);
}
  
void TextEditorApp::DisplayDocContents(TextEditorBuffer* doc){
  // PushID for repeated code
  ImGui::PushID(doc);
  ImGui::Text("Document \"%s\"", doc->Name);
  ImGui::Text("Location \"%s\"", doc->Path);
  ImGui::PushStyleColor(ImGuiCol_Text, doc->Color);
  // Display the buffer in a textfield. ImGui::InputTextMultiline() returns true when text is edited.
  ImGui::PushFont(CodeFont);
  ImVec2 space = ImGui::GetContentRegionAvail();
  if(ImGui::InputTextMultiline(
			       "##docContent",
			       doc->Data,
			       sizeof(doc->Data),
			       ImVec2(-1, space.y - 60),
			       ImGuiInputTextFlags_None)
     ) doc->Dirty = true;
  ImGui::PopFont();
  ImGui::PopStyleColor();
  ImGui::Spacing();
  ImGui::SetNextItemShortcut(ImGuiMod_Ctrl | ImGuiMod_Shift | ImGuiKey_R, ImGuiInputFlags_Tooltip);
  if (ImGui::Button("Rename.."))
    // Renames the TextEditorBuffer, not the file. This will be the filename when saved, kind of 'Save As...'
    {
      RenamingDoc = doc;
      RenamingStarted = true;
    }
  ImGui::SameLine();
  
  ImGui::SetNextItemShortcut(ImGuiMod_Ctrl | ImGuiKey_R, ImGuiInputFlags_Tooltip);
  if (ImGui::Button("Refresh"))
    doc->DoRefreshShader();
  
  ImGui::SameLine();
  ImGui::SetNextItemShortcut(ImGuiMod_Ctrl | ImGuiKey_S, ImGuiInputFlags_Tooltip);
  if (ImGui::Button("Save"))
    doc->DoSave();
  
  ImGui::SameLine();
  ImGui::SetNextItemShortcut(ImGuiMod_Ctrl | ImGuiKey_W, ImGuiInputFlags_Tooltip);
  if (ImGui::Button("Close"))
    CloseQueue.push_back(doc);

  ImGui::Spacing();

  
  ImGui::ColorEdit3("color", &doc->Color.x);  // Useful to test drag and drop and hold-dragged-to-open-tab behavior.
  ImGui::PopID();
}
void TextEditorApp::DisplayMenuBar() {
  // Menu
  if (ImGui::BeginMenuBar()){
    if (ImGui::BeginMenu("File")){
      int open_count = 0;
      for (TextEditorBuffer& doc : Documents)
	open_count += doc.Open ? 1 : 0;
	    
      if (ImGui::MenuItem("Open...")){
	OpenDocument();
	            
      }
      if (ImGui::BeginMenu("Recent", open_count < Documents.Size)){
	for (TextEditorBuffer& doc : Documents)
	  if (!doc.Open && ImGui::MenuItem(doc.Name))
	    doc.DoOpen();
	ImGui::EndMenu();
      }
      if (ImGui::MenuItem("Close All Documents", NULL, false, open_count > 0))
	for (TextEditorBuffer& doc : Documents)
	  CloseQueue.push_back(&doc);
      if (ImGui::MenuItem("Exit"))
	Visible = false;
      ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
  }
}
// Display context menu for the Document
void TextEditorApp::DisplayDocContextMenu(TextEditorBuffer* doc){
  if (!ImGui::BeginPopupContextItem())
    return;
  
  char buf[256];
  sprintf(buf, "Save %s", doc->Name);
  if (ImGui::MenuItem(buf, "Ctrl+S", false, doc->Open))
    doc->DoSave();
  if (ImGui::MenuItem("Rename...", "Ctrl+R", false, doc->Open))
    RenamingDoc = doc;
  if (ImGui::MenuItem("Close", "Ctrl+W", false, doc->Open))
    CloseQueue.push_back(doc);
  ImGui::EndPopup();
}

void TextEditorApp::NotifyOfDocumentsClosedElsewhere()
{
  for (TextEditorBuffer& doc : Documents)
    {
      if (!doc.Open && doc.OpenPrev)
	ImGui::SetTabItemClosed(doc.Name);
      doc.OpenPrev = doc.Open;
    }
}

int TextEditorApp::RequestDocumentID() { return Documents.Size; }

void TextEditorApp::Show() {
  // Options
  static bool opt_reorderable = true;
  static ImGuiTabBarFlags opt_fitting_flags = ImGuiTabBarFlags_FittingPolicyDefault_;

  bool window_contents_visible = ImGui::Begin("Shader Editor", &Visible, ImGuiWindowFlags_MenuBar|ImGuiWindowFlags_NoScrollbar|ImGuiWindowFlags_NoScrollWithMouse);
  if (!window_contents_visible)
    {
      ImGui::End();
      return;
    }

  DisplayMenuBar();
  ImGui::Separator();

  // Submit Tab Bar and Tabs
  {
    ImGuiTabBarFlags tab_bar_flags = (opt_fitting_flags) | (opt_reorderable ? ImGuiTabBarFlags_Reorderable : 0);
    tab_bar_flags |= ImGuiTabBarFlags_DrawSelectedOverline;
    if (ImGui::BeginTabBar("##tabs", tab_bar_flags))
      {
	if (opt_reorderable) NotifyOfDocumentsClosedElsewhere();
	if(ImGui::TabItemButton(!ShowBufferList ? "LIST" : "EDITOR", ImGuiButtonFlags_None)){
	  ShowBufferList = !ShowBufferList;
#ifdef DEBUG_ENABLED
	  puts("LIST pressed");
	  puts(std::to_string(ShowBufferList).c_str());
#endif
	  ImGui::EndTabBar();
	  // Ending the tabbar when pressed prevents the button from mixing in with the tabs.
	} else {
	  if (!ShowBufferList) // Run the for loop: Submit Tabs
	    for (TextEditorBuffer& doc : Documents){
	      if (!doc.Open) continue; // skip if closed
	      // Get the name for the tab
	      char doc_name_buf[64];
	      GetTabName(&doc, doc_name_buf, sizeof(doc_name_buf));
	      // Set the flags for the tab
	      ImGuiTabItemFlags tab_flags =
		(doc.Dirty ? ImGuiTabItemFlags_UnsavedDocument : 0) |
		(doc.Popup ? ImGuiTabItemFlags_SetSelected : 0);
	      doc.Popup = false;
	      
	      bool visible = ImGui::BeginTabItem(doc_name_buf, &doc.Open, tab_flags);
	      
	      // Cancel attempt to close when unsaved add to save queue so we can display a popup.
	      if (!doc.Open && doc.Dirty){
		// weird, I expect doc.Open to always be false here, but the test is needed
		doc.Open = true;
		CloseQueue.push_back(&doc);
	      }
	      
	      DisplayDocContextMenu(&doc);
	      
	      if (visible){
		DisplayDocContents(&doc);
		ImGui::EndTabItem();
	      }
	  }
	  // Show buffer list
	  else {
	    static bool refresh = true;
	    float x = ImGui::GetContentRegionAvail().x;
	    float y = ImGui::GetTextLineHeight() + 2.;
	    ImVec2 size = ImVec2(x, y);
	    
	    static std::filesystem::path dir{expandHome(DEFAULT_LOAD_PATH)};
	    ImGui::PushFont(CodeFont);
	    if (CustomButton("./\t(refresh)", size)) refresh = true;
	    if (CustomButton("../\t(up directory)", size)) {
	      dir = dir.parent_path();
	      refresh = true;
	    }
	    ImGui::Separator();

	    static std::vector<std::filesystem::path> dirs;
	    static std::vector<std::filesystem::path> files;
	    
	    static std::vector<std::filesystem::path> visited;
	    
	    if(refresh){
	      dirs.clear();
	      files.clear();
	      for(auto const& dir_entry : std::filesystem::directory_iterator{dir})
		if(dir_entry.is_directory())
		  dirs.push_back(dir_entry);
	      for(auto const& dir_entry : std::filesystem::directory_iterator{dir})
		if(dir_entry.is_regular_file())
		  files.push_back(dir_entry);
	      refresh = false;
	    }
	    ImU32 dirColor = IM_COL32(127,255,130,100);
            for(std::filesystem::path dir_entry : dirs){
	      std::string label = dir_entry.filename().c_str();
	      label += "/";
	      if(CustomButton(label.c_str(), size, dirColor)){
		dir = dir_entry;
		refresh = true;
	      }
	    }
	    
	    ImGui::Separator();

	    for(std::filesystem::path dir_entry : files)
	      CustomButton(dir_entry.filename().c_str(), size);

	    ImGui::Separator();

	    ImGui::PopFont();
	  } 
	  ImGui::EndTabBar();
	}
      }
  }

  // Display renaming UI
  if (RenamingDoc != NULL){
    if (RenamingStarted)
      ImGui::OpenPopup("Rename");
    if (ImGui::BeginPopup("Rename")){
      ImGui::SetNextItemWidth(ImGui::GetFontSize() * 30);
      if (ImGui::InputText("###Name", RenamingDoc->Name, IM_ARRAYSIZE(RenamingDoc->Name), ImGuiInputTextFlags_EnterReturnsTrue)){
	ImGui::CloseCurrentPopup();
	RenamingDoc = NULL;
      }
      if (RenamingStarted) ImGui::SetKeyboardFocusHere(-1);
      ImGui::EndPopup();
    }
    else {
      RenamingDoc = NULL;
    }
    RenamingStarted = false;
  }

  // Display closing confirmation UI
  if (!CloseQueue.empty()){
    int close_queue_unsaved_documents = 0;
    for (int n = 0; n < CloseQueue.Size; n++)
      if (CloseQueue[n]->Dirty) close_queue_unsaved_documents++;

    if (close_queue_unsaved_documents == 0) {
      // Close documents when all are unsaved
      for (int n = 0; n < CloseQueue.Size; n++) CloseQueue[n]->DoForceClose();

      CloseQueue.clear();
    }
    else {
      if (!ImGui::IsPopupOpen("Save?")) ImGui::OpenPopup("Save?");
      if (ImGui::BeginPopupModal("Save?", NULL, ImGuiWindowFlags_AlwaysAutoResize)){
	ImGui::Text("Save change to the following items?");
	float item_height = ImGui::GetTextLineHeightWithSpacing();
	if (ImGui::BeginChild(ImGui::GetID("frame"), ImVec2(-FLT_MIN, 6.25f * item_height), ImGuiChildFlags_FrameStyle))
	  for (TextEditorBuffer* doc : CloseQueue)
	    if (doc->Dirty)
	      ImGui::Text("%s", doc->Name);
	ImGui::EndChild();

	ImVec2 button_size(ImGui::GetFontSize() * 7.0f, 0.0f);
	if (ImGui::Button("Yes", button_size)){
	  for (TextEditorBuffer* doc : CloseQueue){
	    if (doc->Dirty)
	      doc->DoSave();
	    doc->DoForceClose();
	  }
	  CloseQueue.clear();
	  ImGui::CloseCurrentPopup();
	}
	ImGui::SameLine();
	if (ImGui::Button("No", button_size)){
	  for (TextEditorBuffer* doc : CloseQueue)
	    doc->DoForceClose();
	  CloseQueue.clear();
	  ImGui::CloseCurrentPopup();
	}
	ImGui::SameLine();
	if (ImGui::Button("Cancel", button_size)){
	  CloseQueue.clear();
	  ImGui::CloseCurrentPopup();
	}
	ImGui::EndPopup();
      }
    }
  }
  
  ImGui::End();
}


void TextEditorApp::OpenDocument() {
  char* path;
  std::string data;
  nfdresult_t result;
  std::uintmax_t fileSize = 0;
  
  result = NFD_OpenDialog("frag,vert;shader", loadPath.c_str(), &path); //no spaces in filter tested on GNOME picker
  if(result == NFD_OKAY){
    fileSize = getFileSize(path);
    if (fileSize > TEXT_BUFFER_SIZE) {
      std::cerr << "Failed to open file: file too large! (" << fileSize << " bytes, max=" << TEXT_BUFFER_SIZE << ")\n" << path << std::endl;
      return;
    }
    std::ifstream file(path);
    if(!file.is_open()){
      std::cerr << "Failed to open file: " << path << std::endl;
    }
    else {
      std::string line;
      while(std::getline(file, line)){
	data += line;
	data+="\n";
      }
      data += "\0";
    }
    file.close();
    const char* name = strrchr(path, '/'); // actually the index of the last slash, hence name + 1
    if (!name) name = strrchr(path,'\\');
    if (name) name++;
    char location[128];
    strncpy(location, path, strlen(path) - strlen(name)); // copy last slash too
    location[strlen(path) - strlen(name)] = '\0'; // after last slash add null terminator
    
    TextEditorBuffer doc = TextEditorBuffer(RequestDocumentID(), name ? name : path, data.c_str(), true, location);
    Documents.push_front(doc);
    AppendToRecentDocuments(path);
    ImGui::SetTabItemClosed(doc.Name);
#ifdef DEBUG_ENABLED
    //fs::path fullpath = constructFullPath(location, name); 
    //puts(fullpath.c_str());
    puts(path);
    puts(location);
    puts(name); 
    puts(doc.Data);
    puts(std::to_string(fileSize).c_str());
#endif
  }
}

void TextEditorApp::AppendToRecentDocuments(const char* text) {
  std::deque<std::string> lines;
  std::string line;
  std::string newLine(text);

  // Read all lines into deque
  std::ifstream fileIn(RECENT_DOCS_FILE);
  while (std::getline(fileIn, line)) {
    lines.push_back(line);
  }
  fileIn.close();

  // Insert new line at the top
  lines.push_front(newLine);

  // Remove duplicate of new line from subsequent lines
  for (auto it = std::next(lines.begin()); it != lines.end(); ++it) {
    if (*it == newLine) {
      lines.erase(it);
      break;
    }
  }

  // Ensure only the 10 most recent lines are kept
  while (lines.size() > 10) {
    lines.pop_back();
  }

  // Write updated lines back to the file
  std::ofstream fileOut(RECENT_DOCS_FILE, std::ios::trunc);
  if (fileOut) {
    for (const auto& l : lines) {
      fileOut << l << "\n";
    }
  } else {
    std::cerr << "Failed to open file: " << RECENT_DOCS_FILE << std::endl;
  }
}

bool TextEditorApp::CustomButton(const char* label, const ImVec2& size, const ImU32 textcolor) {
    ImGui::PushID(label);  // Push a unique ID to avoid ImGui ID conflicts
    static std::string s;
    bool selected = false;
    // Draw an invisible button to capture input
    if (ImGui::InvisibleButton(label, size)) {
        s = label;
	selected = true;
    }
    ImU32 fillColor = Colors.DefaultButtonColor;
    if (strcmp(s.c_str(), label) == 0) fillColor = Colors.ActiveButtonColor;

    ImDrawList* drawList = ImGui::GetWindowDrawList();
    ImVec2 pos = ImGui::GetItemRectMin();
    ImVec2 pos_end = ImGui::GetItemRectMax();

    // Draw a filled rectangle in the button area
    drawList->AddRectFilled(pos, pos_end, fillColor, -1);  // Rounded corners

    // Draw the label in the center
    ImVec2 text_size = ImGui::CalcTextSize(label);
    ImVec2 text_pos = ImVec2(
			     pos.x + 1.0f, // pos.x + (size.x - text_size.x) * 0.5f,
			      pos.y + (size.y - text_size.y) * 0.5f
    );

    drawList->AddText(text_pos, textcolor, label);


    ImGui::PopID();
    return selected;  // Returns true if button was clicked
}

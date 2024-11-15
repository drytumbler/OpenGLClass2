// TextEditorApp.cpp

//-----------------------------------------------------------------------------
// [SECTION] Example App: Documents Handling / ShowTextEditorApp()
//-----------------------------------------------------------------------------

#include "ui.h"
//#include "TextEditorApp.h"
//#include "TextEditorBuffer.h"
#include "config.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include <vector>

ImFont* TextEditorApp::CodeFont = nullptr;

TextEditorApp::TextEditorApp(){
  //Documents.push_back(TextEditorBuffer(0, "Empty Shader", "#version 330 core\n\nvoid main()\n{\n\n\tgl_FragColor = vec4( vec3( 0.0, 0.0, 0.0 ), 1.0 ); \n}\n", true));
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
  if (ImGui::Button("Refresh")){
    //quick hqck to rehresh vertex shader
    std::string vertexData = "";
    vertexData += "#version 330 core\n";
    vertexData += "layout (location = 0) in vec3 vertexPos;\n";
    vertexData += "layout (location = 1) in vec3 vertexColor;\n";
    vertexData += "out vec3 fragmentColor;\n";
    vertexData += "out vec2 fragmentTexCoord;\n";
    //out vec3 vertexNormal;
    //out vec3 crntPos;
    vertexData += "uniform mat4 model;\n";
    vertexData += "uniform mat4 view;\n";
    vertexData += "uniform mat4 proj;\n";
    vertexData += "uniform vec2 res;\n";
    vertexData += "uniform float time;\n";
    vertexData += "void main(){\n";
    vertexData += "  gl_Position = proj * view * model * vec4(vertexPos, 1.0f);\n";
    //fragmentColor = vertexColor;
    vertexData += "    fragmentTexCoord = (vertexPos.xy + 1.0) / 2.0;\n";
    vertexData += "}\n";
    Shader::pushShader(vertexData.c_str(), doc->Data);
  }
  //doc->DoRefreshShader();
  
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
void TextEditorApp::DisplayMenuBar(int open_count) {
  // Menu
  if (ImGui::BeginMenuBar()){
    if (ImGui::BeginMenu("File")){
	    
      if (ImGui::MenuItem("Open...")){
	OpenDocument();
	ShowBufferList = false;
      }
      if (ImGui::BeginMenu("Project", open_count > 0)){
	for (TextEditorBuffer& doc : Documents)
	  if (ImGui::MenuItem(doc.Name)){
	    doc.DoOpen();
	    ShowBufferList = false;
	    doc.Popup = true;
	  }
	ImGui::EndMenu();
      }
      if (!ShowBufferList && ImGui::MenuItem("Close All Tabs", NULL, false, open_count > 0))
	for (TextEditorBuffer& doc : Documents)
	  CloseQueue.push_back(&doc);
      if (ImGui::MenuItem("Hide"))
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

void TextEditorApp::Show(ImVec2 space) {
  // Options
  static bool opt_reorderable = true;
  static ImGuiTabBarFlags opt_fitting_flags = ImGuiTabBarFlags_FittingPolicyDefault_;
  
  float menuHeight = ImGui::GetFrameHeight();
  ImVec2 size = ImVec2(space.x * MAINX, space.y); //space.y has menuHeight already deducted
  ImVec2 pos = ImVec2(0.0, menuHeight);
  ImGui::SetNextWindowSize(size);
  ImGui::SetNextWindowPos(pos);

  bool window_contents_visible = ImGui::Begin("Shader Editor", &Visible, ImGuiWindowFlags_MenuBar|ImGuiWindowFlags_NoScrollbar|ImGuiWindowFlags_NoScrollWithMouse);// |ImGuiWindowFlags_NoScrollbar|ImGuiWindowFlags_NoScrollWithMouse

  if (!window_contents_visible)
    {
      ImGui::End();
      return;
    }

  int open_count = 0;
  for (TextEditorBuffer& doc : Documents)
    open_count += doc.Open ? 1 : 0;
  DisplayMenuBar(open_count);

  ImGui::Separator();

  // Submit Tab Bar and Tabs
  {
    ImGuiTabBarFlags tab_bar_flags = (opt_fitting_flags) | (opt_reorderable ? ImGuiTabBarFlags_Reorderable : 0);
    tab_bar_flags |= ImGuiTabBarFlags_DrawSelectedOverline;
    if (ImGui::BeginTabBar("##tabs", tab_bar_flags))
      {
	if (opt_reorderable) NotifyOfDocumentsClosedElsewhere();
	if(ImGui::TabItemButton(!ShowBufferList ? "BROWSER" : "EDITOR", ImGuiButtonFlags_None)){
	  ShowBufferList = !ShowBufferList;
#ifdef DEBUG_ENABLED
	  puts(ShowBufferList ? "BROWSER" : "EDITOR");
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
	    if(ImGui::TabItemButton("TEXTURES", ImGuiButtonFlags_None)) {
	      ui::Texter.Visible = true;
	    }
	    if(ImGui::TabItemButton("MESHES", ImGuiButtonFlags_None));
	    if(ImGui::TabItemButton("LAYOUT", ImGuiButtonFlags_None));

	    float x = ImGui::GetContentRegionAvail().x;
	    float y = ImGui::GetTextLineHeightWithSpacing();
	    ImVec2 entrySize = ImVec2(x, y);

	    ImVec2 pos = ImGui::GetItemRectMin();
	    ImVec2 pos_end = ImGui::GetItemRectMax();
	    ImVec2 entrySizeWithSpacing = ImVec2(pos_end.x - pos.x, pos_end.y - pos.y + 2.);
	    
	    static std::filesystem::path dir = DEFAULT_LOAD_PATH;
	    //if (ui::Refresh) dir = ui::GetBrowserPath();
	    ImGui::PushFont(CodeFont);
	    //ui::SetBrowserPath(dir);
	    
	    ImGui::BeginChild("browser", ImVec2(0, ImGui::GetContentRegionAvail().y / 2.), ImGuiChildFlags_ResizeY, ImGuiWindowFlags_NoScrollbar|ImGuiWindowFlags_NoScrollWithMouse);
	    if(ImGui::IsMouseDown(0) && (ImGui::GetContentRegionAvail().y > (size.y - 150) ))
	      ImGui::SetWindowSize(ImVec2(0, size.y - 150));
	    
          ImGui::BeginChild("nav", ImVec2(0, entrySizeWithSpacing.y * 2.), 0, ImGuiWindowFlags_NoScrollbar|ImGuiWindowFlags_NoScrollWithMouse);	    
	    if (CustomButton("./\t(refresh)", entrySize)) {
	      //	      selected = dir;
	      ui::Refresh();
	    }
	    if (CustomButton("../\t(up directory)", entrySize)) {
	      dir = dir.parent_path();
	      ui::SetBrowserPath(dir);
	      //	      selected = dir;
	      //ui::Refresh();
	    }
	  ImGui::EndChild();

            ImGui::Separator();

	    static std::vector<std::filesystem::path> dirs;
	    static std::vector<std::filesystem::path> files;
	    static std::filesystem::path selected;
	    ImGui::Text(ui::BrowserPath.c_str());
	    //static std::vector<std::filesystem::path> visited;
	    
	    if(!ui::EditorReady){
	      static bool startFlag = true;
	      if (startFlag){
		startFlag = false;
		ui::SetBrowserPath(dir);
	      }
	      dir = ui::GetBrowserPath();
	      if (!dir.has_extension() && ((std::filesystem::directory_entry)dir).is_directory() && !dir.empty()){
	      dirs.clear();
	      files.clear();
	      for(auto const& dir_entry : std::filesystem::directory_iterator{dir})
		if(dir_entry.is_directory())
		  dirs.push_back(dir_entry);
	      for(auto const& dir_entry : std::filesystem::directory_iterator{dir})
		if(dir_entry.is_regular_file())
		  files.push_back(dir_entry);
	      }
	      ui::EditorReady = true;
	    }

            ImU32 dirColor = IM_COL32(127,255,130,100);

	    ImGui::BeginChild("dirs", ImVec2(0, entrySizeWithSpacing.y * fmin(7., dirs.size())), ((dirs.size() > 5) ? 0 : ImGuiChildFlags_AutoResizeY) | ImGuiChildFlags_ResizeY, 0);
	    
            for(std::filesystem::path dir_entry : dirs){
	      std::string label = dir_entry.filename().c_str();
	      label += "/";
	      if(CustomButton(label.c_str(), entrySize, dirColor)){
		dir = dir_entry.c_str();
		puts(dir.c_str());
		ui::SetBrowserPath(dir);
		files.clear();
		selected = dir;
		for(auto const& dir_entry : std::filesystem::directory_iterator{dir})
		  if(dir_entry.is_regular_file())
		    files.push_back(dir_entry);
		//ui::Refresh = true;
	      }
	    }
	    // if(ui::Refresh && strcmp(dir.c_str(), ui::GetBrowserPath().c_str()) != 0)
	    //  ui::SetBrowserPath(dir);
	  ImGui::EndChild();
	    
	    ImGui::Separator();

	    ImGui::BeginChild("files", ImVec2(0, 0));
            for(std::filesystem::path dir_entry : files)
	      if(CustomButton(dir_entry.filename().c_str(), entrySize)) ui::SetBrowserPath(dir_entry);
	  ImGui::EndChild();
	    

	    ImGui::PopFont();

	ImGui::EndChild();

	ImGui::Separator();
	    
	ImGui::BeginChild("static");
	    if(ImGui::Button("INFO")) State::GetInstance().Report();
	    ImGui::Text("STATIC");
	    ImGui::Text(selected.c_str());

	  if (ImGui::BeginTable("##bg", 1, ImGuiTableFlags_RowBg)){
	    for (auto doc : Documents){
	      ImGui::TableNextRow();
	      ImGui::Text(doc.Name);
	    }
	  }
	  ImGui::EndTable();
	  
	  
	  if (ImGui::BeginTable("table1", 3, ImGuiTableFlags_HighlightHoveredColumn))
	    {
	      for (int row = 0; row < 4; row++)
		{
		  ImGui::TableNextRow();
		  for (int column = 0; column < 3; column++)
		    {
		      ImGui::TableSetColumnIndex(column);
		      ImGui::Text("Row %d Column %d", row, column);
		    }
		}
	      ImGui::EndTable();
	    }
      ImGui::EndChild();
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
      for(TextEditorBuffer& doc : Documents){
	doc.Popup = false;
	if(!strcmp(constructFullPath(doc.Path, doc.Name).c_str(), path)){
	  doc.Popup = true;
	  doc.DoOpen();
	  return;
	}
      }
      
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

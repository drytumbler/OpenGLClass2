#include "TextEditorApp.h"
#include "TextEditorBuffer.h"

// This example is taken from http://learnopengl.com/
// http://learnopengl.com/code_viewer.php?code=getting-started/hellowindow2
// the cherno -- https://www.youtube.com/watch?v=H2E3yO0J7TM&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&index=3
// freecodecamp -- https://www.youtube.com/watch?v=45MIykWJ-C4&t=1237s
// The code originally used GLEW, I replaced it with Glad

// put defines on top to prevent redefine warning (handled in config.h)


#include "config.h"


#include "nfd/nfd.h"

// put undefines here or in config.h
//#undef UI_ENABLED

#ifdef UI_ENABLED
#include "ui.h"
ui UI = ui();
#endif
  

// functions declarations:
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void setupGLFW();
void setupImGui(GLFWwindow* window);
GLFWwindow *createWindow();
void saveScreenshotToFile(std::string filename, int windowWidth,
                          int windowHeight);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void window_size_callback(GLFWwindow *window, int width, int height);

int session_id;

int main()
{
  setupGLFW();
  GLFWwindow *window = createWindow();
  glClearColor(0.719f, 0.185f, 0.165f, 1.0f);
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  //setupImGui(window); 
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
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);



  static TextEditorApp Editor;

  while (!glfwWindowShouldClose(window))

    {
      glfwPollEvents();

      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();      
      ImGui::NewFrame();
      
      Editor.Show();

      glClearColor(0.019f, 0.0185f, 0.0165f, 1.0f);
  
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); // skip this to not render ui (eg. screenshot)

      
      // Swap the screen buffers
      glfwSwapBuffers(window);
    }
  
  //cleanup
  

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  
  glfwDestroyWindow(window);
  glfwTerminate();
  std::cout << "Thank You!" << std::endl;
  return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
  static bool ctrlPressed;
  static bool altPressed;

    if (key == GLFW_KEY_LEFT_CONTROL) {
        if (action == GLFW_PRESS)
            ctrlPressed = true;
        else if (action == GLFW_RELEASE)
            ctrlPressed = false;
    }
  
    if (key == GLFW_KEY_LEFT_ALT || key == GLFW_KEY_RIGHT_ALT) {
        if (action == GLFW_PRESS)
            altPressed = true;
        else if (action == GLFW_RELEASE)
            altPressed = false;
    }
  
  if (key == GLFW_KEY_F4 && action == GLFW_PRESS && altPressed)
    glfwSetWindowShouldClose(window, GL_TRUE);

#ifdef UI_ENABLED
  if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
    if(!UI.uiHovered)
      UI.Toggle();
#endif

  if (key == GLFW_KEY_P && action == GLFW_RELEASE && ctrlPressed)
        saveScreenshotToFile("scrn.tga", WIDTH, HEIGHT);
}

// Mouse position callback function
void mousePositionCallback(GLFWwindow* window, double xpos, double ypos) {
#ifdef DEBUG_ENABLED
  //std::cout << "Mouse Position: (" << xpos << ", " << ypos << ")\n";
#endif
}

// Mouse button callback function
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
#ifdef DEBUG_ENABLED
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    std::cout << "Left Mouse Button Pressed\n";
  else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
    std::cout << "Left Mouse Button Released\n";
    }
#endif
}


void setupGLFW()
{
  // Init GLFW
  glfwInit();
  // Set all the required options for GLFW
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  glfwWindowHint(GLFW_SAMPLES, 4); // 4x MSAA

  std::cout << "Starting GLFW context, OpenGL " << glfwGetVersionString() << std::endl;
}

GLFWwindow *createWindow()
{
  // Create a GLFWwindow object that we can use for GLFW's functions
  GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "prEditor", NULL, NULL);

  if (window == NULL)
    {
      std::cout << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      return nullptr;
    }

  glfwMakeContextCurrent(window);

  // Set the required callback functions
  glfwSetKeyCallback(window, key_callback);
  // Set mouse callbacks
  glfwSetCursorPosCallback(window, mousePositionCallback);
  glfwSetMouseButtonCallback(window, mouseButtonCallback);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetWindowSizeCallback(window, window_size_callback);
  

  glfwSetWindowPos(window, 200, 100);
  
  // Load OpenGL functions, gladLoadGL returns the loaded version, 0 on error.
  int version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  if (version == 0)
    {
      std::cout << "Failed to initialize OpenGL context" << std::endl;
      return nullptr;
    }

  // Define the viewport dimensions
  
  glViewport(0, 0, WIDTH, HEIGHT);
  return window;
}

void saveScreenshotToFile(std::string filename, int windowWidth, int windowHeight) {
  //filenames are automatically numbered
  static int n = 0;
  std::size_t dot = filename.find_last_of('.');
  std::string name = filename.substr(0, dot);
  std::string ext = (dot == std::string::npos) ? ".tga" : filename.substr(dot);
  std::string dir = "screens/" + std::to_string(session_id) + "/";


    try {
      std::filesystem::create_directories(dir);
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error creating directory: " << e.what() << "\n";
        
        // Fallback to a user-accessible directory in the home folder
        std::cerr << "Saving to  " << std::string(std::getenv("HOME")) << "/screens/" <<  std::to_string(session_id) << "\n";
        dir = std::string(std::getenv("HOME")) + "/screens/" + std::to_string(session_id) + "/";
        std::filesystem::create_directories(dir);
    }
  
  std::string nfilename = dir + name + std::to_string(n) + ext;
  const int numberOfPixels = windowWidth * windowHeight * 3;
  unsigned char pixels[numberOfPixels];
  
  glPixelStorei(GL_PACK_ALIGNMENT, 1);
  glReadBuffer(GL_FRONT);

  glReadPixels(0, 0, windowWidth, windowHeight, GL_BGR, GL_UNSIGNED_BYTE, pixels);
  
  FILE *outputFile = fopen(nfilename.c_str(), "w");
  short header[] = {0, 2, 0, 0, 0, 0, (short) windowWidth, (short) windowHeight, 24};
  
  fwrite(&header, sizeof(header), 1, outputFile);
  fwrite(pixels, numberOfPixels, 1, outputFile);
  fclose(outputFile);
  n++;
  printf("Finish writing to file.\n");
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void window_size_callback(GLFWwindow* window, int width, int height)
{
  
}

void setupImGui(GLFWwindow* window) {
#ifdef UI_ENABLED
  UI.SetWindow(window);
  UI.Setup();
  assert(UI.GetSetupDone() && "UI_ERROR: Setup error");

  std::cout << "\nPress SPACEBAR to enable the menu.\n";
#else
#ifdef UI_ENABLED
  std::cout << "UI_DISABLED\n";
#endif
#endif
  
}

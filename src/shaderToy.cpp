// This example is taken from http://learnopengl.com/
// http://learnopengl.com/code_viewer.php?code=getting-started/hellowindow2
// the cherno -- https://www.youtube.com/watch?v=H2E3yO0J7TM&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&index=3
// freecodecamp -- https://www.youtube.com/watch?v=45MIykWJ-C4&t=1237s
// The code originally used GLEW, I replaced it with Glad

//#include "config.h"
#include "Material.h"
#include "TriangleMesh.h"
#include "Shader.h"
#include "VBO.h"
#include "Camera.h"
//#include "math.h"

//#define abs(X) ((X < 0) ? -X : X)

#define WIDTH 400
#define HEIGHT 300

#include "../include/imgui/imgui.h"
#include "../include/imgui/imgui_impl_glfw.h"
#include "../include/imgui/imgui_impl_opengl3.h"
#include "../include/nfd/nfd.h"

//#define GL_SILENCE_DEPRECATION
bool uiOn = false;
bool uiRequestExit = false;

static void ShowOptionsMenu()
{
  //IMGUI_DEMO_MARKER("Examples/Menu");
    ImGui::MenuItem("(demo menu)", NULL, false, false);
    if (ImGui::MenuItem("New")) {}
    if (ImGui::MenuItem("Open", "Ctrl+O")) {}
    if (ImGui::BeginMenu("Open Recent"))
    {
        if (ImGui::BeginMenu("More.."))
        {

            if (ImGui::BeginMenu("Recurse.."))
            {
                ShowOptionsMenu();
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenu();
    }
    if (ImGui::MenuItem("Save", "Ctrl+S")) {}
    if (ImGui::MenuItem("Save As..")) {}

    ImGui::Separator();
    //IMGUI_DEMO_MARKER("Examples/Menu/Options");
    if (ImGui::BeginMenu("Options"))
    {
        static bool enabled = true;
        ImGui::MenuItem("Enabled", "", &enabled);
        ImGui::BeginChild("child", ImVec2(0, 60), ImGuiChildFlags_Borders);
        for (int i = 0; i < 10; i++)
            ImGui::Text("Scrolling Text %d", i);
        ImGui::EndChild();
        static float f = 0.5f;
        static int n = 0;
        ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
        ImGui::InputFloat("Input", &f, 0.1f);
        ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
        ImGui::EndMenu();
    }

    //IMGUI_DEMO_MARKER("Examples/Menu/Colors");
    if (ImGui::BeginMenu("Colors"))
    {
        float sz = ImGui::GetTextLineHeight();
        for (int i = 0; i < ImGuiCol_COUNT; i++)
        {
            const char* name = ImGui::GetStyleColorName((ImGuiCol)i);
            ImVec2 p = ImGui::GetCursorScreenPos();
            ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol)i));
            ImGui::Dummy(ImVec2(sz, sz));
            ImGui::SameLine();
            ImGui::MenuItem(name);
        }
        ImGui::EndMenu();
    }

    // Here we demonstrate appending again to the "Options" menu (which we already created above)
    // Of course in this demo it is a little bit silly that this function calls BeginMenu("Options") twice.
    // In a real code-base using it would make senses to use this feature from very different code locations.
    if (ImGui::BeginMenu("Options")) // <-- Append!
    {
      //IMGUI_DEMO_MARKER("Examples/Menu/Append to an existing menu");
        static bool b = true;
        ImGui::Checkbox("SomeOption", &b);
        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Disabled", false)) // Disabled
    {
        IM_ASSERT(0);
    }
    if (ImGui::MenuItem("Checked", NULL, true)) {}
    ImGui::Separator();
    if (ImGui::MenuItem("Quit", "Alt+F4")) { uiRequestExit=true; }
}
int main()
{
  setupGLFW();
  GLFWwindow *window = createWindow();

  const char* glsl_version = "#version 130";

  // Setup Dear ImGui context
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
  
  
  // Set the clear color
  glClearColor(0.719f, 0.185f, 0.165f, 1.0f);
  
  // Setup viewport
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  
  // Stuff
  GLint maxVertices, maxIndices;
  glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &maxVertices);
  glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &maxIndices);
  std::cout << "Max vertices: " << maxVertices << ", Max indices: " << maxIndices << std::endl;

  // Canvas setup 
  const std::vector<float> vertices = {
    -1.0, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 
    1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 
    1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 
    -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 
  };
  
  const std::vector<GLuint> indices = {
    0, 1, 2, 0, 2, 3
  };
  
  // Vertex Attributes
  std::vector<VertexAttribute> attributes = {
    VertexAttribute(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0, false),
    VertexAttribute(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)), false),
    VertexAttribute(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)), false)
  };
  
  // Create buffers
  VBO* vbo = new VBO(vertices, attributes);
  IBO* ibo = new IBO(indices);
  // Gather VBOs (if more then one)
  std::vector<VBO*> VBOs;
  VBOs.push_back(vbo);
  
  
  TriangleMesh* triangle = new TriangleMesh(VBOs, ibo); // it's a square!
  triangle->Report();
  
  Material* material = new Material("../src/textures/lenna.png");
  Material* mask = new Material("../src/textures/mask.png");
  Material* sandstone = new Material("../src/textures/sandstone.png");
  Material* moon = new Material("../src/textures/moon.png");
  
  // TODO -> check filename
  //setup shaders
  Shader shader(
		"../src/shaders/shadertoy.vert",
		"../src/shaders/shadertoy.frag"
		);
  
  //bind the shader
  
  //shader.Activate();
  //setup texture uniforms - moved to while loop

  
    
  //setup blending options
  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ZERO);
  
  //enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glDepthRange(0.1f, 100.0f);

  //enable multisampling (needs GLFW setup ..)
  glEnable(GL_MULTISAMPLE);

 
  // uniforms
  float time=0.0f;
  glm::vec2 res(1.0f * width, 1.0f * height);
  
  GLuint u_Time, u_Resolution;
  
  // Game loop
  while (!glfwWindowShouldClose(window) && !uiRequestExit)
    {
      glViewport(0, 0, width, height);
      glfwPollEvents();
      // Start the Dear ImGui frame
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();

 ImGui::NewFrame();
 if (ImGui::BeginMainMenuBar()){
         if (ImGui::BeginMenu("Options"))
        {
            ShowOptionsMenu();
            ImGui::EndMenu();
        }
        
        ImGui::EndMainMenuBar();
 }
      if(uiOn){
      
       ImGui::Begin("shaderToy.cpp");
       if (ImGui::Button("choose", ImVec2(50.,18.))){
	 nfdchar_t *outPath = NULL;
	 nfdresult_t result = NFD_OpenDialog( NULL, "../src/shaders/", &outPath);
	 if ( result == NFD_OKAY ) {
	   puts("Success!");
	   puts(outPath);
	   free(outPath);
	 }
	 else if ( result == NFD_CANCEL ) {
	   puts("User pressed cancel.");
	 }
	 else {
	   printf("Error: %s\n", NFD_GetError() );
	 }
       }
       ImGui::End();
      }
      // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
      glClearColor(0.019f, 0.0185f, 0.0165f, 1.0f);
      time = (float)glfwGetTime();
       
      

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // Apply the shader
      shader.Activate();
      
      // Update uniforms
      glUniform1f(u_Time, time);
      glUniform2fv(u_Resolution, 1, &res[0]);

      //setup MVP
      glm::mat4 model = glm::mat4(1.0f);
      glm::mat4 view = glm::mat4(1.0f);
      glm::mat4 proj = glm::mat4(1.0f);
      
      view = glm::translate(view, glm::vec3(0.0f, 0.0f, 1.0f));
      proj = glm::perspective(PI / 2.0f, 1.0f, 0.1f, 100.0f);
      //proj = glm::ortho(-1.0f, 1.0f, -1.0f / (width / (float)height), 1.0f / (width / (float)height), 0.1f, 100.0f);

      //model = glm::rotate(model, 0.08f * PI * time, glm::vec3(0.0,1.0,0.0));
      

      unsigned int u_Model = glGetUniformLocation(shader.ID, "model");
      unsigned int u_View  = glGetUniformLocation(shader.ID, "view");
      unsigned int u_Projection = glGetUniformLocation(shader.ID, "proj");

      u_Time = glGetUniformLocation(shader.ID, "time");
      u_Resolution = glGetUniformLocation(shader.ID, "res");

      glUniform1i(glGetUniformLocation(shader.ID, "material"), 0);
      glUniform1i(glGetUniformLocation(shader.ID, "mask"), 1);
      glUniform1i(glGetUniformLocation(shader.ID, "sandstone"), 2);
      glUniform1i(glGetUniformLocation(shader.ID, "moon"), 3);

      
      glm::vec3 cameraPosition = {0.0, 0.0, -1.0};
      glm::vec3 cameraTarget = {0.0, 0.0, 0.0};
      glm::vec3 up = {0.0f, 1.0f, 0.0f};


      view = glm::lookAt(cameraPosition, cameraTarget, up);

      glUniformMatrix4fv(u_Model, 1, GL_FALSE, glm::value_ptr(model));
      glUniformMatrix4fv(u_View, 1, GL_FALSE, glm::value_ptr(view));
      glUniformMatrix4fv(u_Projection, 1, GL_FALSE, glm::value_ptr(proj));
      
      
      
      //camera.Update(PI / 2.0f, 0.0f, 10.0f, shader, "camMatrix");
      
      // Draw the triangle
      sandstone->Use();
      material->Use();
      moon->Use();
      mask->Use();
      
      triangle->draw();
      shader.Refresh(window);

      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
      
      // Swap the screen buffers
      glfwSwapBuffers(window);
    }
  
  //cleanup
  shader.Delete();
  delete triangle;
  delete material;
  delete mask;
  delete vbo;
    
  // Terminate GLFW and ImGui
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);

  if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
    uiOn = !uiOn;
}

// Mouse position callback function
void mousePositionCallback(GLFWwindow* window, double xpos, double ypos) {
  std::cout << "Mouse Position: (" << xpos << ", " << ypos << ")\n";
}

// Mouse button callback function
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    std::cout << "Left Mouse Button Pressed\n";
  else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
    std::cout << "Left Mouse Button Released\n";
    saveScreenshotToFile("scrn.tga", WIDTH, HEIGHT);
    }
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
  glfwWindowHint(GLFW_SAMPLES, 16); // 4x MSAA

  std::cout << "Starting GLFW context, OpenGL " << glfwGetVersionString() << std::endl;
}

GLFWwindow *createWindow()
{
  // Create a GLFWwindow object that we can use for GLFW's functions
  GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "shaderToy", NULL, NULL);

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
    const int numberOfPixels = windowWidth * windowHeight * 3;
    unsigned char pixels[numberOfPixels];

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, windowWidth, windowHeight, GL_BGR, GL_UNSIGNED_BYTE, pixels);

    FILE *outputFile = fopen(filename.c_str(), "w");
    short header[] = {0, 2, 0, 0, 0, 0, (short) windowWidth, (short) windowHeight, 24};

    fwrite(&header, sizeof(header), 1, outputFile);
    fwrite(pixels, numberOfPixels, 1, outputFile);
    fclose(outputFile);

    printf("Finish writing to file.\n");
}

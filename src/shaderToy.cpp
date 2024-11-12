// This example is taken from http://learnopengl.com/
// http://learnopengl.com/code_viewer.php?code=getting-started/hellowindow2
// the cherno -- https://www.youtube.com/watch?v=H2E3yO0J7TM&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&index=3
// freecodecamp -- https://www.youtube.com/watch?v=45MIykWJ-C4&t=1237s
// The code originally used GLEW, I replaced it with Glad

// put defines on top to prevent redefine warning (handled in config.h)
#define WIDTH 1280
#define HEIGHT 796
#define MAIN_WINDOW_NAME "shaderNvader"
#include "config.h"

#include "Material.h"
#include "TriangleMesh.h"
#include "Shader.h"
#include "VBO.h"
#include "Camera.h"
#include "Primitive.h"

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
void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
void mousePositionCallback(GLFWwindow* window, double xpos, double ypos);

int session_id;

int main()
{
  setupGLFW();
  GLFWwindow *window = createWindow();

  //GLFWwindow* secondWindow = createWindow();

  glClearColor(0.719f, 0.185f, 0.165f, 1.0f);
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  
  setupImGui(window); 
  std::cout << "Press CTRL+S to grab a screenshot.\n";
  std::cout << "Press ALT+F4 to quit.\n" << std::endl; 
  
  //generate a random session token
  std::srand(std::time(nullptr));
  session_id = rand();
    

  // Stuff
#ifdef DEBUG_ENABLED
  std::cout << "DEBUG_ENABLED\n";
  GLint maxVertices, maxIndices;
  glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &maxVertices);
  glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &maxIndices);
  std::cout << "Max vertices: " << maxVertices << ", Max indices: " << maxIndices << std::endl;
#endif


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


  // Primitive
  Primitive primate = Primitive(glm::vec3(0.0,2.0,0.0), 0.5, "none");
  Primitive orb = Primitive(glm::vec3(0.0,2.0,0.0), 0.5, "none");
  
  // Create camera
  Camera camera = Camera(WIDTH, HEIGHT, glm::vec3(0.0f, 3.0f, -5.0f));
  camera.direction = normalize(glm::vec3(0.0, 0.0, 1.0));
  camera.setKeyVector(glm::vec3(-1.0,1.0,1.0));
  camera.setMouseVector(glm::vec3(-1.0,1.0,1.0));

  // Create buffers
  VBO* vbo = new VBO(vertices, attributes);
  IBO* ibo = new IBO(indices);
  // Gather VBOs (if more then one)
  std::vector<VBO*> VBOs;
  VBOs.push_back(vbo);
  
  
  TriangleMesh* triangle = new TriangleMesh(VBOs, ibo); // it's a square!
  #ifdef DEBUG_ENABLED
  triangle->Report();
  #endif
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

  // MARK  not needed for current setup
  
  
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
  glm::vec2 res(1.0f * width, 1.0f * height); // do i need to pass this?
  
  GLuint u_Time, u_Resolution;
  
  // Game loop

#ifdef UI_ENABLED
  while (!glfwWindowShouldClose(window) && !UI.uiRequestExit)
#else
  while (!glfwWindowShouldClose(window))
#endif
    {
      glfwMakeContextCurrent(window);

#ifdef UI_ENABLED
      //      UI.Run();
#endif

      glClearColor(0.019f, 0.0185f, 0.0165f, 1.0f);
      time = (float)glfwGetTime();
       
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // Apply the shader
      //      shader.Activate();
      Shader::StaticShader.Activate();
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

      //unsigned int u_Camera= glGetUniformLocation(shader.ID, "camera");
      //      camera.direction = normalize(camera.direction);
      //camera.Update(PI / 2., 0.1, 10.);
      camera.ExportDir(shader, "rd");
      camera.ExportRight(shader, "ri");
      camera.ExportPos(shader, "ro");
      
#ifdef UI_ENABLED
      if(!UI.uiHovered)
	camera.Inputs(window);
#else
      camera.Inputs(window);
#endif

      
      primate.Export(shader, "primate");
      orb.position = glm::vec3(sin(time), 2.0, cos(time));
      orb.Export(shader, "orb");
      
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
      
      triangle->Draw();
      shader.Refresh(window);

#ifdef UI_ENABLED
      UI.Run();
      UI.Render();
#endif
      glfwPollEvents();
      // Swap the screen buffers
      glfwSwapBuffers(window);
    }
  
  //cleanup
  
  shader.Delete();
  delete triangle;
  delete material;
  delete mask;
  delete vbo;
  

  
#ifdef UI_ENABLED
  UI.Quit();
#endif
  
  glfwDestroyWindow(window);
  //glfwDestroyWindow(secondWindow);
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
  GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, MAIN_WINDOW_NAME, NULL, NULL);

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
  UI.Editor.Colors.SetColorsToDefault();
  assert(UI.GetSetupDone() && "UI_ERROR: Setup error");
  std::cout << "\nPress SPACEBAR to enable the menu.\n";
#else
#ifdef UI_ENABLED
  std::cout << "UI_DISABLED\n";
#endif
#endif
  
}

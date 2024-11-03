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

#define abs(X) ((X<0)?-X:X)

int main()
{
  std::cout << "Size of float: " << sizeof(float) << " bytes\n";
  std::cout << "Size of int: " << sizeof(int) << " bytes\n";
  
  const std::vector<float> vertices = {
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 
    1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 
    1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 
    -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 
  };

  const std::vector<GLuint> indices = {
    0, 1, 3, 1, 2, 3
  };
  
  setupGLFW();
  GLFWwindow *window = createWindow();
  
  // Set the clear color
  glClearColor(0.19f, 0.185f, 0.165f, 1.0f);
  
  // Setup viewport
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);

  // Stuff
  GLint maxVertices, maxIndices;
  glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &maxVertices);
  glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &maxIndices);
  std::cout << "Max vertices: " << maxVertices << ", Max indices: " << maxIndices << std::endl;

  std::vector<VertexAttribute> attributes = {
    VertexAttribute(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0, false),
    VertexAttribute(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)), false),
    VertexAttribute(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)), false)
  };
  
  VBO* vbo = new VBO(vertices, attributes);
  IBO* ibo = new IBO(indices, indices.size());


  
  std::vector<VBO*> VBOs;
  VBOs.push_back(vbo);

  
  TriangleMesh* triangle = new TriangleMesh(VBOs, ibo); // it's a square!
  triangle->Report();
  
  Material* material = new Material("../src/textures/lenna.png");

  Material* mask = new Material("../src/textures/mask.png");

  Material* sandstone = new Material("../src/textures/sandstone.png");
  
  
  //setup shaders
  Shader shader(
		"../src/shaders/vertex.shader",
		"../src/shaders/fragment.shader"
		);
  
  //bind the shader
  //glUseProgram(shader.ID); //always load shader before applying further changes
  shader.Activate();
  //setup texture uniforms
  glUniform1i(glGetUniformLocation(shader.ID, "material"), 0);
  glUniform1i(glGetUniformLocation(shader.ID, "mask"), 1);
  glUniform1i(glGetUniformLocation(shader.ID, "sandstone"), 2);
  
  

  //Camera camera(width, height, glm::vec3(-0.25f, 0.0f, 2.22f));
  
  //setup blending options
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ZERO);
  glDepthFunc(GL_LESS);
  glDepthRange(0.1f, 100.0f);

  glEnable(GL_MULTISAMPLE);

 
  // uniforms
  float time=0.0f, scale=1.0f;
  GLuint u_Time, u_Scale;
  u_Time = glGetUniformLocation(shader.ID, "time");
  u_Scale = glGetUniformLocation(shader.ID, "scale");
  
  // Game loop
  while (!glfwWindowShouldClose(window))
    {
      // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
      glfwPollEvents();
       
      time = (float)glfwGetTime();
      scale = sin(time);
  
      glClearColor(0.019f, 0.0185f, 0.0165f, 1.0f);

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // Apply the shader
      shader.Activate();
      
      // Update uniforms
      glUniform1f(u_Scale, scale);
      glUniform1f(u_Time, time);

      //setup MVP
      glm::mat4 model = glm::mat4(1.0f);
      glm::mat4 view = glm::mat4(1.0f);
      glm::mat4 proj = glm::mat4(1.0f);
      
      view = glm::translate(view, glm::vec3(0.0f, 0.0f, -1.0f));
      proj = glm::perspective(PI / 2.0f, 1.0f * width / height, 0.1f, 100.0f);

      //      model = glm::rotate(model, 0.08f * PI * time, glm::vec3(0.0,1.0,0.0));
      

      unsigned int u_Model = glGetUniformLocation(shader.ID, "model");
      unsigned int u_View  = glGetUniformLocation(shader.ID, "view");
      unsigned int u_Projection = glGetUniformLocation(shader.ID, "proj");

      
      glm::vec3 cameraPosition = {0.0, 0.0, 0.0};
      glm::vec3 cameraTarget = {0.0, 0.0, 0.0};
      glm::vec3 up = {0.0f, 1.0f, 0.0f};

      //view = glm::lookAt(cameraPosition, cameraTarget, up);

      glUniformMatrix4fv(u_Model, 1, GL_FALSE, glm::value_ptr(model));
      glUniformMatrix4fv(u_View, 1, GL_FALSE, glm::value_ptr(view));
      glUniformMatrix4fv(u_Projection, 1, GL_FALSE, glm::value_ptr(proj));
      
      
      
      //camera.Update(PI / 2.0f, 0.0f, 10.0f, shader, "camMatrix");
      
      // Draw the triangle
      material->Use();
      mask->Use();
      sandstone->Use();
      
      triangle->draw();

      // Swap the screen buffers
      glfwSwapBuffers(window);
    }
  
  //cleanup
  shader.Delete();
  delete triangle;
  delete material;
  delete mask;
  delete vbo;
    
  // Terminates GLFW, clearing any resources allocated by GLFW.
  glfwTerminate();
  return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

// Mouse position callback function
void mousePositionCallback(GLFWwindow* window, double xpos, double ypos) {
  std::cout << "Mouse Position: (" << xpos << ", " << ypos << ")\n";
}

// Mouse button callback function
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    std::cout << "Left Mouse Button Pressed\n";
  else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    std::cout << "Left Mouse Button Released\n";
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
  GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);

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

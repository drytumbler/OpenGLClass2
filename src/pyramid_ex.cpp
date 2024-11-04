// This example is taken from http://learnopengl.com/
// http://learnopengl.com/code_viewer.php?code=getting-started/hellowindow2
// the cherno -- https://www.youtube.com/watch?v=H2E3yO0J7TM&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&index=3
// freecodecamp -- https://www.youtube.com/watch?v=45MIykWJ-C4&t=1237s
// The code originally used GLEW, I replaced it with Glad
// Compile command : cmake - S..- B../ build - DCMAKE_BUILD_TYPE = Debug && cmake-- build../ build
                                  
//#include "config.h"
#include "Material.h"
#include "TriangleMesh.h"
#include "Shader.h"
#include "VBO.h"
#include "Camera.h"
#include <glm/ext/matrix_transform.hpp>
//#include "math.h"


int main()
{
  std::cout << "Size of float: " << sizeof(float) << " bytes\n";
  std::cout << "Size of int: " << sizeof(int) << " bytes\n";
  /*
  const std::vector<float> vertices = {
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 
    1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 
    1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 
    -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 
  };
  */

  // Vertices coordinates
  std::vector<float> vertices =
    
    { //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
      -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
      -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 1.0f,      0.0f, -1.0f, 0.0f, // Bottom side
      0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 1.0f, 1.0f,      0.0f, -1.0f, 0.0f, // Bottom side
      0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 1.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
      
      -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
      -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 1.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
      0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 0.5f, 1.0f,     -0.8f, 0.5f,  0.0f, // Left Side
      
      -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 2.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
      0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
      0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 0.5f, 1.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
      
      0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
      0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 1.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
      0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 0.5f, 1.0f,      0.8f, 0.5f,  0.0f, // Right side
      
      0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 1.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
      -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
      0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 0.5f, 1.0f,      0.0f, 0.5f,  0.8f  // Facing side
    };
  
  // Indices for vertices order
  std::vector<unsigned int> indices =
    {
      0, 1, 2, // Bottom side
      0, 2, 3, // Bottom side
      4, 6, 5, // Left side
      7, 9, 8, // Non-facing side
      10, 12, 11, // Right side
      13, 15, 14 // Facing side
    };
  
  std::vector<float> lightVertices =
    { //     COORDINATES     //
      -0.1f, -0.1f,  0.1f,
      -0.1f, -0.1f, -0.1f,
      0.1f, -0.1f, -0.1f,
      0.1f, -0.1f,  0.1f,
      -0.1f,  0.1f,  0.1f,
      -0.1f,  0.1f, -0.1f,
      0.1f,  0.1f, -0.1f,
      0.1f,  0.1f,  0.1f
    };
  
  std::vector<VertexAttribute> lightAttributes = {
    VertexAttribute(4, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0, false)
  };
  
  std::vector<unsigned int> lightIndices =
    {
      0, 1, 2,
      0, 2, 3,
      0, 4, 7,
      0, 7, 3,
      3, 7, 6,
      3, 6, 2,
      2, 6, 5,
      2, 5, 1,
      1, 5, 4,
      1, 4, 0,
      4, 5, 6,
      4, 6, 7
    };
  
  
  
  /*
    const std::vector<GLuint> indices = {
    0, 1, 3, 1, 2, 3
    };
  */
  
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
    VertexAttribute(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*) 0, false),
    VertexAttribute(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*) (3 * sizeof(float)), false),
    VertexAttribute(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*) (6 * sizeof(float)), false),
    VertexAttribute(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*) (8 * sizeof(float)), false),
  };
  
  VBO* vbo = new VBO(vertices, attributes);
  IBO* ibo = new IBO(indices, indices.size());
  
  VBO* lightVBO = new VBO(lightVertices, lightAttributes);
  IBO* lightIBO = new IBO(lightIndices, lightIndices.size());
  
  
  std::vector<VBO*> VBOs;
  VBOs.push_back(vbo);
  
  std::vector<VBO*> lightVBOs;
  lightVBOs.push_back(lightVBO);

  
  TriangleMesh* triangle = new TriangleMesh(VBOs, ibo); // it's a square!
  triangle->Report();

  TriangleMesh* cube = new TriangleMesh(lightVBOs, lightIBO);
  cube->Report();
  
  Material* material = new Material("../src/textures/lenna.png");

  Material* mask = new Material("../src/textures/mask.png");

  Material* sandstone = new Material("../src/textures/sandstone.png");
  
  
  //setup shaders
  Shader shader(
		"../src/shaders/default.vert",
		"../src/shaders/default.frag"
		);

  Shader lightShader(
		    "../src/shaders/light.vert",
		    "../src/shaders/light.frag"
		     );


  glm::vec4 lightColor = glm::vec4(1.0f, 0.9f, 0.7f, 1.0f);

  // setup models
  glm::vec3 lightPos = glm::vec3(1.7f, 0.05f, 0.5f);
  glm::mat4 lightModel = glm::mat4(1.0f);
  lightModel = glm::translate(lightModel, lightPos);

  glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::mat4 pyramidModel = glm::mat4(1.0f);
  pyramidModel = glm::translate(pyramidModel, pyramidPos);

  glm::mat3 normalMatrix = glm::mat3(1.0f);
  glUniformMatrix3fv(glGetUniformLocation(shader.ID, "normal"), 1, GL_FALSE, glm::value_ptr(normalMatrix));

  lightShader.Activate();
  glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
  
  //bind the shader
  //glUseProgram(shader.ID); //always load shader before applying further changes
  shader.Activate();
  glUniform4f(glGetUniformLocation(shader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.a);
  glUniform3f(glGetUniformLocation(shader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
  //setup texture uniforms
  glUniform1i(glGetUniformLocation(shader.ID, "material"), 0);
  glUniform1i(glGetUniformLocation(shader.ID, "mask"), 1);
  glUniform1i(glGetUniformLocation(shader.ID, "sandstone"), 2);
  
  glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));

  Camera camera(width, height, glm::vec3(0.0f, 0.0f, 1.0f));
  
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
      //      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      
      glfwPollEvents();
      camera.Inputs(window);
       
      time = (float)glfwGetTime();
      scale = sin(time);
  
      glClearColor(0.019f, 0.0185f, 0.0165f, 1.0f);

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      pyramidModel = glm::rotate(pyramidModel, glm::radians(1.0f), glm::vec3(0.0f,1.0f,0.0f));
      normalMatrix = glm::transpose(glm::inverse(glm::mat3(pyramidModel)));

      //lightModel = glm::mat4(1.0f);
      //lightModel = glm::translate(lightModel, -lightPos);
      //lightModel = glm::rotate(lightModel, glm::radians(1.0f), glm::vec3(0.0f,1.0f,0.0f));
      //lightModel = glm::translate(lightModel, lightPos);

      // Apply the shader
      shader.Activate();
      glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
      glUniformMatrix3fv(glGetUniformLocation(shader.ID, "normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
      camera.Update(PI / 2.0f, 0.1f, 100.0f);
      camera.Export(shader, "camMatrix");
      
      // Update uniforms
      glUniform1f(u_Scale, scale);
      glUniform1f(u_Time, time);


      
      
      // Draw the triangle
      material->Use();
      mask->Use();
      sandstone->Use();
      
      triangle->draw();
      lightShader.Activate();
      glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
      camera.Export(lightShader, "camMatrix");
      cube->draw();

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

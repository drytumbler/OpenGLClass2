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
#include "Model.h"

//#include "math.h"

// functions:
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void setupGLFW();
GLFWwindow *createWindow();

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
      
      -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 1.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
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

  std::vector<float> planeVertices = {
    -15., 0.1, 15., 1., 1., 1., -1., -1., 0., 1., 0.,
    15., -0.1, 15., 1., 1., 1., 1., -1., 0., 1., 0.,
    15., 0.1, -15., 1., 1., 1., 1., 1., 0., 1., 0.,
    -15., -0.1, -15., 1., 1., 1., -1., 1., 0., 1., 0.
  };
  std::vector<GLuint> planeIndices = { 0, 1, 2, 0, 2, 3 };

  setupGLFW();
  GLFWwindow *window = createWindow();
  glfwSetWindowPos(window, 1920-500, 1080-500);
  
  Material* material = new Material("../src/textures/lenna.png");
  Material* mask = new Material("../src/textures/mask.png");
  Material* sandstone = new Material("../src/textures/sandstone.png");
  Material* sandstone1 = new Material("../src/textures/TH_Yellow_Bricks_baseColor.png");
  Material* sandstone2 = new Material("../src/textures/TH_Yellow_Bricks_roughness.png");
  Material* sandstone3 = new Material("../src/textures/TH_Yellow_Bricks_normal.png");
  Material* beach1 = new Material("../src/textures/Smooth_Beach_Sand_baseColor.png");
  Material* beach2 = new Material("../src/textures/Smooth_Beach_Sand_mask.png");
  Material* beach3 = new Material("../src/textures/Smooth_Beach_Sand_normal.png");

  
  std::vector<VertexAttribute> attributes = {
    VertexAttribute(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*) 0, false),
    VertexAttribute(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*) (3 * sizeof(float)), false),
    VertexAttribute(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*) (6 * sizeof(float)), false),
    VertexAttribute(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*) (8 * sizeof(float)), false),
  };
  
  VBO* vbo = new VBO(vertices);
  IBO* ibo = new IBO(indices);
  
  VBO* lightVBO = new VBO(lightVertices);
  IBO* lightIBO = new IBO(lightIndices);

  VBO* planeVBO = new VBO(planeVertices);
  IBO* planeIBO = new IBO(planeIndices);
 
  TriangleMesh* triangle = new TriangleMesh(vbo, attributes, ibo); // it's a square!
  TriangleMesh* cube = new TriangleMesh(lightVBO, lightAttributes, lightIBO);
  TriangleMesh* plane = new TriangleMesh(planeVBO, attributes, planeIBO);
#ifdef DEBUG_ENABLED
  triangle->Report();
  cube->Report();
  plane->Report();
#endif
  
  //setup shaders
  Shader shader(
		"../src/shaders/default.vert",
		"../src/shaders/phong.frag"
		);

  Shader lightShader(
		    "../src/shaders/light.vert",
		    "../src/shaders/light.frag"
		     );
  

  Shader planeShader(
		    "../src/shaders/plane.vert",
		    "../src/shaders/plane.frag"
		     );
  
  // setup models

  Model* model = new Model("../src/models/teapot_bezier2.tris");

  
  glm::vec4 lightColor = glm::vec4(0.97f, 1.0f, 1.0f, 1.0f);
  glm::vec3 lightPos = glm::vec3(10.7f, 30.05f, 20.5f);
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
  glUniform4fv(glGetUniformLocation(shader.ID, "lightColor"), 1, glm::value_ptr(lightColor));
  glUniform3f(glGetUniformLocation(shader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
  //setup texture uniforms


  
  glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
  
  // Set the clear color
  glClearColor(0.19f, 0.185f, 0.165f, 1.0f);
  
  // Setup viewport
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  
  // Stuff
  GLint maxVertices, maxIndices;
  glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &maxVertices);
  glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &maxIndices);
  std::cout << '\a';
  std::cout << "Max vertices: " << maxVertices << ", Max indices: " << maxIndices << std::endl;
  
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

  
  // Game loop

  while (!glfwWindowShouldClose(window))
    {
      // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
      //      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      
      glfwPollEvents();
      camera.Inputs(window);
       
      time = (float)glfwGetTime();
      //printf("%f\n", time);

      float f = (0.5 + 0.5 * sin(time * 0.25));
      glClearColor(1.1 * f * lightColor.r * .5, f*f * lightColor.g * .5, f*f * lightColor.b * .5, lightColor.a );
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      pyramidModel = glm::rotate(pyramidModel, glm::radians(.02f), glm::vec3(0.0f,1.0f,0.0f));
      normalMatrix = glm::transpose(glm::inverse(glm::mat3(pyramidModel)));
 
      //lightModel = glm::mat4(1.0f);
      //lightModel = glm::translate(lightModel, -lightPos);
      //lightModel = glm::rotate(lightModel, glm::radians(1.0f), glm::vec3(0.0f,1.0f,0.0f));

      lightModel = glm::translate(lightModel, -lightPos);
      lightPos = glm::vec3(10.5, 30.7 * (0.5 + 0.5 * sin(time * 0.25)), 15.8);
      lightModel = glm::translate(lightModel, lightPos);
      lightColor = glm::vec4(0.8, 0.9f * pow((0.8 + 0.2 * sin(time * 0.25)), .3), 0.9f * pow((0.65 + 0.35 * sin(time * 0.25)), .6), 1.0f);
      //std::cout << "(" << lightPos.x << "," << lightPos.y << "," <<  lightPos.z << ")" << std::endl;
      // Apply the shader
      shader.Activate();
      glUniform1i(glGetUniformLocation(shader.ID, "material"), 0);
      glUniform1i(glGetUniformLocation(shader.ID, "mask"), 1);
      glUniform1i(glGetUniformLocation(shader.ID, "sandstone"), 2);
      glUniform1i(glGetUniformLocation(shader.ID, "sandstone1"), 3);
      glUniform1i(glGetUniformLocation(shader.ID, "sandstone2"), 4);
      glUniform1i(glGetUniformLocation(shader.ID, "sandstone3"), 5);
      
      glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
      glUniformMatrix3fv(glGetUniformLocation(shader.ID, "normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
      glUniform3fv(glGetUniformLocation(shader.ID, "lightPos"), 1, glm::value_ptr(lightPos));
      glUniform4fv(glGetUniformLocation(shader.ID, "lightColor"), 1, glm::value_ptr(lightColor));

      camera.Update(PI / 4.0f, 0.1f, 100.0f);
      camera.Export(shader, "camMatrix");
      
      // Update uniforms

      glUniform1f( glGetUniformLocation(shader.ID, "time"), time);


      
      
      // Draw the triangle
      material->Use();
      mask->Use();
      sandstone->Use();
      sandstone1->Use();
      sandstone2->Use();
      sandstone3->Use();

      
      //      triangle->Draw(shader, camera);
      model->Draw(shader, camera);

      planeShader.Activate();
      glUniform1i(glGetUniformLocation(planeShader.ID, "beach1"), 6);
      glUniform1i(glGetUniformLocation(planeShader.ID, "beach2"), 7);
      glUniform1i(glGetUniformLocation(planeShader.ID, "beach3"), 8);
      glUniformMatrix4fv(glGetUniformLocation(planeShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
      glUniform3fv(glGetUniformLocation(planeShader.ID, "lightPos"), 1, glm::value_ptr(lightPos));
      glUniform4fv(glGetUniformLocation(planeShader.ID, "lightColor"), 1, glm::value_ptr(lightColor));
      glUniform1f( glGetUniformLocation(planeShader.ID, "time"), time);

      beach1->Use();
      beach2->Use();
      beach3->Use();
      camera.Export(planeShader, "camMatrix");
      plane->Draw(planeShader, camera);
      
      lightShader.Activate();
      glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
      glUniform3fv(glGetUniformLocation(lightShader.ID, "lightPos"), 1,glm::value_ptr(lightPos));
      glUniform4fv(glGetUniformLocation(lightShader.ID, "lightColor"), 1, glm::value_ptr(lightColor));
      glUniform1f( glGetUniformLocation(lightShader.ID, "time"), time);

      camera.Export(lightShader, "camMatrix");
      cube->Draw(lightShader, camera);

      // Swap the screen buffers
      glfwSwapBuffers(window);
    }
  
  //cleanup
  shader.Delete();
  delete triangle;
  delete cube;
  delete material;
  delete mask;
  delete sandstone;
  delete sandstone1;
  delete sandstone2;
  delete sandstone3;

  delete vbo;
  delete lightVBO;
  delete ibo;
  delete lightIBO;

  delete planeVBO;
  delete planeIBO;
  delete beach1;
  delete beach2;
  delete beach3;
  delete plane;

  delete model;
  
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
  //std::cout << "Mouse Position: (" << xpos << ", " << ypos << ")\n";
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
  glfwWindowHint(GLFW_SAMPLES, 4); // 4x MSAA

  glfwWindowHint(GLFW_POSITION_X, 1920);
  glfwWindowHint(GLFW_POSITION_Y, 1080);
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

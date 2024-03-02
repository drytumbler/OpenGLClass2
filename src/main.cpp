// This example is taken from http://learnopengl.com/
// http://learnopengl.com/code_viewer.php?code=getting-started/hellowindow2
// The code originally used GLEW, I replaced it with Glad

#include "config.h"
#include "TriangleMesh.h"
int main()
{

    setupGLFW();
    GLFWwindow *window = createWindow();

    // Set the clear color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    TriangleMesh* triangle = new TriangleMesh();

    //setup shaders
    unsigned int shader = makeShaderProg(
        "../src/shaders/vertex.shader",
        "../src/shaders/fragment.shader"
    );

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        // Render

        // Clear the colorbuffer       
        glClear(GL_COLOR_BUFFER_BIT);

        // Apply the shader
        glUseProgram(shader);

        // Draw the triangle
        triangle->draw();

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }

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

void setupGLFW()
{
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

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

unsigned int makeShaderMod(const std::string& filepath, unsigned int shader_type){
    
    // load the shader code (cpu)
    std::ifstream file;
    std::stringstream bufferedLines;
    std::string line;

    file.open(filepath);
    while (std::getline(file, line)){
        bufferedLines << line << "\n";
    }
    std::string shaderSource = bufferedLines.str();
    const char* shaderSrc = shaderSource.c_str();
    bufferedLines.str("");
    file.close();

    //load and compile the shader module (gpu)
    unsigned int shaderModule = glCreateShader(shader_type);
    glShaderSource(shaderModule, 1, &shaderSrc, NULL);
    glCompileShader(shaderModule);

    //error handling
    int succes;
    glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &succes);
    if(!succes){
        char errorLog[1024];
        glGetShaderInfoLog(shaderModule, 1024, NULL, errorLog);
        std::cout << "Shader Module Compilation Error:\n" <<errorLog << std::endl;

        return 0;
    }

    return shaderModule;
}

unsigned int makeShaderProg(const std::string& vertex_filepath, const std::string& fragment_filepath){
    std::vector<unsigned int> modules;
    modules.push_back(makeShaderMod(vertex_filepath, GL_VERTEX_SHADER));
    modules.push_back(makeShaderMod(fragment_filepath, GL_FRAGMENT_SHADER));

    unsigned int shaderProgram = glCreateProgram();
    for (unsigned int shaderModule : modules){
        glAttachShader(shaderProgram, shaderModule);
    }
    glLinkProgram(shaderProgram);

    //error handling
    int succes;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &succes);
    if(!succes){
        char errorLog[1024];
        glGetProgramInfoLog(shaderProgram, 1024, NULL, errorLog);
        std::cout << "Shader Program Linking Error:\n" <<errorLog << std::endl;

        return 0;
    }
    //clean up
    for (unsigned int shaderModule : modules){
        glDeleteShader(shaderModule);
    }

    return shaderProgram;
}
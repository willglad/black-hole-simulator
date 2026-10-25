#include <algorithm>

#include "include.h"
#include "engine.h"
#include "circle.h"
#include "ray.h"

bool Engine::init() {
    if (!glfwInit()){
        std::cerr << "Failed to initialise GLFW" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(wWidth, wHeight, "Black Hole Simulation", nullptr, nullptr);

    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL(glfwGetProcAddress)){
        std::cerr << "Failed to initialise GLAD" << std::endl;
        glfwDestroyWindow(window);
        window = nullptr;
        glfwTerminate();
        return false;
    }

    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Set intial viewport
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    
    // Compiling vertex and fragment shaders
    std::string vertexSource = loadShaderFile("src/shaders/vertex.glsl");
    std::string fragmentSource = loadShaderFile("src/shaders/fragment.glsl");

    const char* vertexSourcePtr = vertexSource.c_str();
    const char* fragmentSourcePtr = fragmentSource.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    glShaderSource(vertexShader, 1, &vertexSourcePtr, nullptr);
    glShaderSource(fragmentShader, 1, &fragmentSourcePtr, nullptr);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);
    
    int success;
    char infoLog[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success){
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return true;
}

void Engine::framebuffer_size_callback(
    GLFWwindow* window,
    int width,
    int height
){

    auto* engine = static_cast<Engine*>(
        glfwGetWindowUserPointer(window)
    );

    if (height > 0) 
        engine->aspectRatio = static_cast<float>(width) / static_cast<float>(height);

    glViewport(0, 0, width, height);
}

void Engine::addCircle(const Circle& c) {
    // Push back for each vertex
    for (auto i : c.vertices){
        // Position
        staticVertices.push_back(i.x);
        staticVertices.push_back(i.y);
        staticVertices.push_back(i.z);
    
        // Alpha
        float alpha = 1.0f;
        staticVertices.push_back(alpha);
    }
    circles.push_back(c);
}

void Engine::submitRay(const Ray& r){
    // Add ray to rays
    rays.push_back(r);
    addRay(r);
}

void Engine::addRay(const Ray& r){
    for (size_t i = 0; i < r.positionHistory.size(); i++){
        // Alpha
        float t = static_cast<float>(i) / static_cast<float>(r.positionHistory.size() - 1);
        float alpha = (r.positionHistory.size() - 1) != 0 ? r.alpha_min + t*(r.alpha_max-r.alpha_min) :  
            r.alpha_max;

        // Push v.x v.y and v.x and the segments alpha
        const auto& v = r.positionHistory[i];
        dynamicVertices.push_back(v[0]);
        dynamicVertices.push_back(v[1]);
        dynamicVertices.push_back(v[2]);
        dynamicVertices.push_back(alpha);
    }
}

bool Engine::buffers(unsigned int& VBO, unsigned int& VAO, std::vector<float>& vertices) {
    // VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glVertexAttribPointer(      // Position
        0,                          // Attribute location
        3,                          // Components per vertex
        GL_FLOAT,                   // Data type
        GL_FALSE,                   // Do not normalise
        4*sizeof(float),            // Stride in bytes
        (void*)0                    // Offset into buffer
    );
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(      // Alpha
        1,                          // Attribute location
        1,                          // Components per vertex
        GL_FLOAT,                   // Data type
        GL_FALSE,                   // Do not normalise
        4*sizeof(float),            // Stride in bytes
        (void*)(3 * sizeof(float))  // Offset into buffer
    );
    glEnableVertexAttribArray(1);

    return true;
}

bool Engine::updateBuffers(unsigned int& VBO, std::vector<float>& vertices){
    // VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);
    return true;
}

void Engine::run(){
    if (window == nullptr){
        std::cerr << "Window is nullptr" << std::endl;
        return;
    }

    // Intialise buffers
    buffers(statVBO, statVAO, staticVertices);
    buffers(dynVBO, dynVAO, dynamicVertices);

    // Initial timer 
    float lastFrame = (float)glfwGetTime();
    while (!glfwWindowShouldClose(window)){
        float currentFrame = (float)glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        // Update all ray object positions -- start by clearing the current dynamicVertices
        dynamicVertices.clear();
        for (auto& i : rays){
             for (auto& j : circles){
                i.update(j, deltaTime/5.0f);
                addRay(i);
             }
        }        

        // Update dynamic buffers
        updateBuffers(dynVBO, dynamicVertices);

        glDisable(GL_DEPTH_TEST);
        render();
    }
}

void Engine::render(){
    glClearColor(background_color[0], background_color[1], background_color[2], background_color[3]);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    
    // Rezising window to keep aspect ratio
    GLint location = glGetUniformLocation(shaderProgram, "aspectRatio");
    glUniform1f(location, aspectRatio);
    if (location == -1){
        std::cerr << "location: " << std::to_string(location) << std::endl; 
    }

    GLint colorLoc = glGetUniformLocation(shaderProgram, "rayColor");
    glUniform3f(colorLoc, 1.0f, 0.6f, 0.0f);

    glBindVertexArray(statVAO);    
    glDrawArrays(GL_TRIANGLES, 0, staticVertices.size() / 3);

    glBindVertexArray(dynVAO);
    glDrawArrays(GL_LINE_STRIP, 0, dynamicVertices.size() / 4);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Engine::cleanup(){
    if (window != nullptr){
        glfwDestroyWindow(window);
        window = nullptr;
    }

    // Delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glfwTerminate();
}
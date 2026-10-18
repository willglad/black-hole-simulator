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
        vertices.push_back(i.x);
        vertices.push_back(i.y);
        vertices.push_back(i.z);
    }
}

bool Engine::buffers() {
    // VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glVertexAttribPointer(
        0,                  // Attribute location
        3,                  // Components per vertex
        GL_FLOAT,           // Data type
        GL_FALSE,           // Do not normalise
        3*sizeof(float),    // Stride in bytes
        (void*)0            // Offset into buffer
    );
    glEnableVertexAttribArray(0);

    return true;
}

void Engine::run(){
    if (window == nullptr){
        std::cerr << "Window is nullptr" << std::endl;
        return;
    }

    while (!glfwWindowShouldClose(window)){
        render();
    }
}

void Engine::render(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    GLint location = glGetUniformLocation(shaderProgram, "aspectRatio");
    glUniform1f(location, aspectRatio);
    if (location == -1){
        std::cerr << "location: " << std::to_string(location) << std::endl; 
    }

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
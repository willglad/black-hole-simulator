#ifndef ENGINE_H
#define ENGINE_H

class Engine {
    public:

        // Window dimensions
        int wWidth      = 600;
        int wHeight     = 600;

        // Simulation dimensions
        double cWidth   = 8e11;
        double cHeight  = 6e11;

        float aspectRatio = float(wWidth) / float(wHeight);

        bool init();
        bool buffers();
        void addCircle(const Circle& c);
        void run();
        void cleanup();

    private:
        GLFWwindow* window = nullptr;

        unsigned int shaderProgram = 0;
        unsigned int vertexShader;
        unsigned int fragmentShader; 

        unsigned int VAO = 0;
        unsigned int VBO = 0;

        std::vector<float> vertices;

        void render();
        static void framebuffer_size_callback(
            GLFWwindow* window,
            int width,
            int height
        );

        std::string loadShaderFile(const std::string& path){
            std::ifstream file(path);

            if (!file.is_open()){
                std::cerr << "Failed to open shader: " << path << '\n';
                return "";
            }

            std::stringstream buffer;
            buffer << file.rdbuf();
            
            return buffer.str();

        }
};

#endif
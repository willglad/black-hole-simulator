#ifndef ENGINE_H
#define ENGINE_H

#include "circle.h"
#include <algorithm>

class Engine {
    public:

        // Window dimensions
        int wWidth      = 600;
        int wHeight     = 600;

        // Simulation dimensions
        double cWidth   = 8e11;
        double cHeight  = 6e11;

        // aspect ratio based on initial window dimensions
        float aspectRatio = float(wWidth) / float(wHeight);

        // Background color
        float background_color[4] = {0.0f, 0.0f, 0.0f, 1.0f};

        bool init();
        bool buffers(unsigned int& VBO, unsigned int& VAO, std::vector<float>& vertices);
        bool updateBuffers(unsigned int& VBO, std::vector<float>& vertices);
        void addCircle(const Circle& c);
        void submitRay(const Ray& r);
        void addRay(const Ray& r);
        void run();
        void cleanup();

    private:
        GLFWwindow* window = nullptr;

        unsigned int shaderProgram = 0;
        unsigned int vertexShader;
        unsigned int fragmentShader; 

        unsigned int dynVAO = 0;
        unsigned int dynVBO = 0;
        unsigned int statVAO = 0;
        unsigned int statVBO = 0;

        std::vector<float> staticVertices;
        std::vector<float> dynamicVertices;
        std::vector<Ray> rays;

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
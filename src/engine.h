#ifndef ENGINE_H
#define ENGINE_H

#include "circle.h"
#include <algorithm>

class Engine {
    public:

        // Window dimensions
        int wWidth      = 600;
        int wHeight     = 600;

        // aspect ratio based on initial window dimensions
        float aspectRatio = float(wWidth) / float(wHeight);

        // scale everything down from dimensionless coords to screen coords
        float scale = 1.0f/4.0f;

        // Background color
        float background_color[4] = {0.0f, 0.0f, 0.0f, 1.0f};

        bool init();                                        // OpenGL setup

        bool buffers(unsigned int& VBO,                     // Assigns buffers, vertex attributes
            unsigned int& VAO,
            std::vector<float>& vertices);

        bool updateBuffers(unsigned int& VBO,               // Updates the buffers
            std::vector<float>& vertices);

        void submitCircle(const Circle& c);                    // Add a circle to the scene
        void submitRay(const Ray& r);                       // Submit a ray to hold in scene, for updates

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

        std::vector<Circle> circles;

        void addRay(const Ray& r);                          // Adds ray trajectory to vertices

        void scaleVertices(std::vector<float>& u, float f); // Scales vertices
        
        void render();                                      // Renders the vertices (dynamic and static)
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

inline std::ostream& operator<<(std::ostream& out, const std::vector<float> v){
    for (auto& i : v){
        out << i;
    }
    return out;
}

#endif
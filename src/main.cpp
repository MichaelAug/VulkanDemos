#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>

const int WIDTH = 800;
const int HEIGHT = 600;

class HelloTriangleApplication {
public:
    void run() {
        InitWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    GLFWwindow* window;

    void InitWindow() {

        // Init GLFW library
        glfwInit();

        // Tell GLFW not to create OpenGL context
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        // Disable screen resizing (can't handle resizable windows for now)
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); 

        //parameters: width, height, title, monitor, OpenGL parameter
        window = glfwCreateWindow(WIDTH,HEIGHT, "Vulkan", nullptr, nullptr);

        std::cout<<"vulkan supported: "<<glfwVulkanSupported()<<std::endl;
    }

    void initVulkan() {

    }

    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void cleanup() {
        glfwDestroyWindow(window);

        glfwTerminate();
    }
};

int main() {
    HelloTriangleApplication app;
    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

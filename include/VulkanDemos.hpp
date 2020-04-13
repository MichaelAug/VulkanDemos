#pragma once
#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <memory>
#include "VulkanInstance.hpp"

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class VulkanDemos
{
public:
    VulkanDemos();

    void run()
    {
        InitWindow();
        vkInstance->initVulkan(window);
        mainLoop();
        cleanup();
    }

private:
    GLFWwindow *window;
    std::unique_ptr<VulkanInstance> vkInstance;

    

    void InitWindow();

    void mainLoop();

    void cleanup();
};
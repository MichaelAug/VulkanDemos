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

// How many frames should the program process concurrently
const int MAX_FRAMES_IN_FLIGHT = 2;

class VulkanDemos
{
public:
    VulkanDemos();

    void run();

private:
    void drawFrame(std::vector<VkSemaphore> &imageAvailableSemaphores, std::vector<VkSemaphore> &renderFinishedSemaphores, size_t &currentFrame);
    GLFWwindow *window;
    std::unique_ptr<VulkanInstance> vkInstance;

    void InitWindow();

    void mainLoop();

    void cleanup();
};
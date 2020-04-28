#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <memory>
#include "VulkanInstance.hpp"
#include "Renderer.hpp"
#include "WindowSurface.hpp"
#include "LogicalDevice.hpp"

class Engine
{
public:
    void Init();

    Engine();

    void run();

    void cleanup();
private:
    std::shared_ptr<LogicalDevice> logicalDevice;
    std::shared_ptr<WindowSurface> windowSurface;
    std::shared_ptr<VulkanInstance> vkInstance;
    std::shared_ptr<Renderer> renderer;

};
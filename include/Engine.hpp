#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <memory>
#include "VulkanInstance.hpp"
#include "Renderer.hpp"
#include "WindowSurface.hpp"

class Engine
{
public:
    Engine();

    void run();

    void cleanup();
private:
    std::shared_ptr<WindowSurface> windowSurface;
    std::shared_ptr<VulkanInstance> vkInstance;
    std::shared_ptr<Renderer> renderer;

};
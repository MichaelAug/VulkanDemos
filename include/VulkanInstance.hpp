#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <stdexcept>
#include <memory>
#include "ValidationLayers.hpp"
#include "DeviceManager.hpp"
#include "WindowSurface.hpp"
#include "ShaderHandler.hpp"

class VulkanInstance
{
public:
	VulkanInstance();

	void initVulkan(GLFWwindow *window);

	void cleanup();
	std::unique_ptr<DeviceManager> deviceManager;

private:
	std::unique_ptr<ValidationLayers> valLayers;

	std::unique_ptr<WindowSurface> windowSurface;
	std::unique_ptr<ShaderHandler> shaderHandler;

	VkInstance instance;

	std::vector<const char *> getRequiredExtensions();

	void createInstance();
};
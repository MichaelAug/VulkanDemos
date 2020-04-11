#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <stdexcept>
#include <memory>
#include "ValidationLayers.hpp"
#include "DeviceManager.hpp"
#include "WindowSurface.hpp"

class VulkanInstance
{
public:
	VulkanInstance();

	void initVulkan(GLFWwindow* window);

	void cleanup();

private:
	std::unique_ptr<ValidationLayers> valLayers;

	std::unique_ptr<DeviceManager> deviceManager;

	std::unique_ptr<WindowSurface> windowSurface;

	VkInstance instance;

	std::vector<const char *> getRequiredExtensions();

	void createInstance();
};
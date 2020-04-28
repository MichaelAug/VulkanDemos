#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <memory>
#include "ValidationLayers.hpp"

class VulkanInstance
{
public:
	VulkanInstance();

	void initVulkan();

	void cleanup();

	VkInstance instance;

private:
	std::unique_ptr<ValidationLayers> valLayers;

	std::vector<const char *> getRequiredExtensions();

	void createInstance();
};
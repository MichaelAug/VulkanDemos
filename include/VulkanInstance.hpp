#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <stdexcept>
#include <memory>
#include "ValidationLayers.hpp"

class VulkanInstance
{
public:
	VulkanInstance();

	void initVulkan();

	void cleanup();

private:
	std::unique_ptr<ValidationLayers> valLayers;

	VkInstance instance;

	void createInstance();

	std::vector<const char *> getRequiredExtensions();
};
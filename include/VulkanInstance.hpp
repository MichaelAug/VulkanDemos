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
	// WON'T NEED WINDOW SURFACE HERE AFTER FULL REFACTOR
	VulkanInstance(std::shared_ptr<WindowSurface> WindowSurface);

	void initVulkan();

	void cleanup();
	std::unique_ptr<DeviceManager> deviceManager;

	VkInstance instance;

private:
	std::weak_ptr<WindowSurface> winSurf;
	std::unique_ptr<ValidationLayers> valLayers;
	std::unique_ptr<ShaderHandler> shaderHandler;

	std::vector<const char *> getRequiredExtensions();

	void createInstance();
};
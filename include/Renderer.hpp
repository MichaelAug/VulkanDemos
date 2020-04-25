#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>
#include "DeviceManager.hpp"
#include "VulkanInstance.hpp"
#include "LogicalDevice.hpp"

// How many frames should the program process concurrently
const int MAX_FRAMES_IN_FLIGHT = 2;

class Renderer
{
public:
	Renderer(std::shared_ptr<VulkanInstance> vulkanInstance, std::shared_ptr<LogicalDevice> logicalDevice);
	void mainLoop(GLFWwindow *window);
	void drawFrame(std::vector<VkSemaphore> &imageAvailableSemaphores, std::vector<VkSemaphore> &renderFinishedSemaphores, size_t &currentFrame);
private:
	std::weak_ptr<VulkanInstance> vkInst;
	std::weak_ptr<LogicalDevice> logicalDevice;
};
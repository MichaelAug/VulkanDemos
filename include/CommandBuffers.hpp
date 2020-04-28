#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <memory>
#include "LogicalDevice.hpp"

class SwapChain;

class CommandBuffers
{
public:
	CommandBuffers(std::shared_ptr<LogicalDevice> logicalDevice);
	void cleanup();
	void createCommandPool(VkSurfaceKHR &surface);
	void createCommandBuffers(const VkRenderPass &renderPass, const VkPipeline &graphicsPipeline, std::unique_ptr<SwapChain> &swpChain);
	std::vector<VkCommandBuffer> commandBuffers;

private:
	VkCommandPool commandPool;
	std::weak_ptr<LogicalDevice> logDev;
};
#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>
#include "VulkanInstance.hpp"
#include "LogicalDevice.hpp"
#include "SyncObjects.hpp"
#include "SwapChain.hpp"
#include "RenderPass.hpp"
#include "GraphicsPipeline.hpp"
#include "CommandBuffers.hpp"
#include "WindowSurface.hpp"

class Renderer
{
public:
	Renderer(std::shared_ptr<VulkanInstance> vulkanInstance, std::shared_ptr<LogicalDevice> logicalDevice, std::shared_ptr<WindowSurface> winSurf);
	void initRendering();
	void mainLoop(GLFWwindow *window);
	void drawFrame(std::vector<VkSemaphore> &imageAvailableSemaphores, std::vector<VkSemaphore> &renderFinishedSemaphores);
	void cleanup();
	void recreateSwapChain();
	void cleanupSwapChain();

private:
	size_t currentFrame = 0;
	std::unique_ptr<SyncObjects> syncObjects;
	std::unique_ptr<SwapChain> swpChain;
	std::unique_ptr<RenderPass> rndPass;
	std::unique_ptr<GraphicsPipeline> gPipeline;
	std::unique_ptr<CommandBuffers> cmdBuffers;

	std::weak_ptr<VulkanInstance> vkInst;
	std::weak_ptr<LogicalDevice> logicalDevice;
	std::weak_ptr<WindowSurface> winSurf;
};
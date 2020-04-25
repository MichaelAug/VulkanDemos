#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include "LogicalDevice.hpp"


class DeviceManager
{
public:
	DeviceManager(std::shared_ptr<LogicalDevice> logDev);

	void cleanup();
	void createSwapChain(const VkSurfaceKHR &surface);
	void createImageViews();
	void createFramebuffers(const VkRenderPass &renderPass);
	void createCommandPool(VkSurfaceKHR &surface);
	void createCommandBuffers(const VkRenderPass &renderPass, const VkPipeline &graphicsPipeline);
	void CreateSyncObjects();
	VkExtent2D swapChainExtent;
	VkFormat swapChainImageFormat;
	VkSwapchainKHR swapChain;
	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;

	std::vector<VkFence> inFlightFences;
	std::vector<VkFence> imagesInFlight;
	std::vector<VkCommandBuffer> commandBuffers;
	size_t currentFrame = 0;
private:
	std::weak_ptr<LogicalDevice> logicalDevice;	
	
	VkCommandPool commandPool;
	std::vector<VkFramebuffer> swapChainFrameBuffers;
	
	
	
	std::vector<VkImage> swapChainImages;

	std::vector<VkImageView> swapChainImageViews;

	DeviceManager(){}
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);

	// Swap extent - resolution of images
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);
};
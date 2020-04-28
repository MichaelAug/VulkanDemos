#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include "LogicalDevice.hpp"

class SwapChain
{
public:
	void createSwapChain(const VkSurfaceKHR &surface, std::shared_ptr<LogicalDevice> &logDev);
	void cleanup(VkDevice &device);
	
	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	std::vector<VkImageView> swapChainImageViews;
	VkFormat swapChainImageFormat;
	std::vector<VkFramebuffer> swapChainFrameBuffers;
	VkExtent2D swapChainExtent;
private:
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);

	// Swap extent - resolution of images
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);
};
#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>

class SwapChain;

class ImageViews
{
public:
	static void createImageViews(std::unique_ptr<SwapChain> &swapChain, VkDevice &device);
	static void cleanup(VkDevice &device, std::vector<VkImageView> &swapChainImageViews);
private:
};
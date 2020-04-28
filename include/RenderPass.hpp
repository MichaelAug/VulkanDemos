#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class RenderPass {
public:

	void createRenderPass(const VkFormat& swapChainImageFormat, const VkDevice &device);
	void cleanup(VkDevice &device);

	VkRenderPass renderPass;
private:
};
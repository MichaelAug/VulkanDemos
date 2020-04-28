#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <memory>

class SwapChain;

class Framebuffers
{
public:
	static void createFramebuffers(const VkRenderPass &renderPass, VkDevice &device, std::unique_ptr<SwapChain> &swpChain);
	static void cleanup(VkDevice &device, std::vector<VkFramebuffer> &swapChainFrameBuffers);

private:
};
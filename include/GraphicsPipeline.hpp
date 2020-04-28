#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <fstream>

class GraphicsPipeline
{
public:
	void createGraphicsPipeline(const VkDevice &device, const VkExtent2D &swapChainExtent, VkRenderPass &renderPass);
	void cleanup(const VkDevice &device);

	VkPipeline graphicsPipeline;
private:
	VkPipelineLayout pipelineLayout;
	static std::vector<char> readFile(const std::string &filename);
	static VkShaderModule createShaderModule(const std::vector<char> &code, const VkDevice &device);
};
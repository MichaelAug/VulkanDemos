#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <fstream>

class ShaderHandler
{
public:
	void createGraphicsPipeline(const VkDevice &device, const VkExtent2D &swapChainExtent);
	void cleanup(const VkDevice &device);
private:
	VkPipelineLayout pipelineLayout;
	static std::vector<char> readFile(const std::string &filename);
	static VkShaderModule createShaderModule(const std::vector<char> &code, const VkDevice &device);
};
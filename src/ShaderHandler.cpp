#include "ShaderHandler.hpp"


void ShaderHandler::createGraphicsPipeline(const VkDevice &device)
{
	//relative path from where the program is run
	auto vertShaderCode = readFile("shaders/vert.spv");
	auto fragShaderCode = readFile("shaders/frag.spv");

	VkShaderModule vertShaderModule = createShaderModule(vertShaderCode, device);
	VkShaderModule fragShaderModule = createShaderModule(fragShaderCode, device);

	VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
	vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
	vertShaderStageInfo.module = vertShaderModule;
	vertShaderStageInfo.pName = "main";

	VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
	fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	fragShaderStageInfo.module = fragShaderModule;
	fragShaderStageInfo.pName = "main";

	VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};

	vkDestroyShaderModule(device, fragShaderModule, nullptr);
	vkDestroyShaderModule(device, vertShaderModule, nullptr);
}

std::vector<char> ShaderHandler::readFile(const std::string& filename)
{
	//start reading at the end of file and in binary mode
	std::ifstream file(filename, std::ios::ate | std::ios::binary);

	if(!file.is_open()) {
		throw std::runtime_error("failed to open file: " + filename);
	}

	//tellg() returns position of the current character
	size_t fileSize = (size_t) file.tellg();

	std::vector<char> buffer(fileSize);

	//go back to beginning of file
	file.seekg(0);
	
	file.read(buffer.data(),fileSize);

	file.close();

	return buffer;
}

VkShaderModule ShaderHandler::createShaderModule(const std::vector<char>& code, const VkDevice &device)
{
	VkShaderModuleCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = code.size();
	createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

	VkShaderModule shaderModule;
	if(vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create shader module");
	}

	return shaderModule;
}

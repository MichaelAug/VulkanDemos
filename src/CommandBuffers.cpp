#include "CommandBuffers.hpp"
#include "PhysicalDevice.hpp"
#include "SwapChain.hpp"

CommandBuffers::CommandBuffers(std::shared_ptr<LogicalDevice> logicalDevice)
{
	logDev = logicalDevice;
}

void CommandBuffers::cleanup()
{
	auto logicalDevice = logDev.lock();
	
	vkDestroyCommandPool(logicalDevice->device, commandPool, nullptr);
}

void CommandBuffers::createCommandPool(VkSurfaceKHR &surface)
{
	auto logicalDevice = logDev.lock();
	QueueFamilyIndices queueFamilyIndices = PhysicalDevice::findQueueFamilies(logicalDevice->getPhysicalDevice(), surface);

	VkCommandPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
	poolInfo.flags = 0; //optional

	if (vkCreateCommandPool(logicalDevice->device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create command pool");
	}
}

void CommandBuffers::createCommandBuffers(const VkRenderPass &renderPass, const VkPipeline &graphicsPipeline, std::unique_ptr<SwapChain> &swpChain)
{
	auto logicalDevice = logDev.lock();
	commandBuffers.resize(swpChain->swapChainFrameBuffers.size());
	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();

	if (vkAllocateCommandBuffers(logicalDevice->device, &allocInfo, commandBuffers.data()) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to allocate command buffers");
	}

	//record command buffers
	for (size_t i = 0; i < commandBuffers.size(); ++i)
	{
		VkCommandBufferBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = 0;				  //optional
		beginInfo.pInheritanceInfo = nullptr; //optional

		if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to begin recording command buffer");
		}

		VkRenderPassBeginInfo renderPassInfo = {};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = renderPass;
		renderPassInfo.framebuffer = swpChain->swapChainFrameBuffers[i];
		renderPassInfo.renderArea.offset = {0, 0};
		renderPassInfo.renderArea.extent = swpChain->swapChainExtent;

		VkClearValue clearColor = {0.0f, 0.0f, 0.0f, 1.0f};
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;

		vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

		/*Parameters:
			command buffer
			vertex count
			first vertex
			first instance*/
		vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

		vkCmdEndRenderPass(commandBuffers[i]);

		if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to record command buffer");
		}
	}
}
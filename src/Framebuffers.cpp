#include "Framebuffers.hpp"
#include "SwapChain.hpp"

void Framebuffers::createFramebuffers(const VkRenderPass &renderPass, VkDevice &device, std::unique_ptr<SwapChain> &swpChain)
{
	swpChain->swapChainFrameBuffers.resize(swpChain->swapChainImageViews.size());

	for (size_t i = 0; i < swpChain->swapChainImageViews.size(); ++i)
	{
		VkImageView attachments[] = {
			swpChain->swapChainImageViews[i]};

		VkFramebufferCreateInfo framebufferInfo = {};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = renderPass;
		framebufferInfo.attachmentCount = 1;
		framebufferInfo.pAttachments = attachments;
		framebufferInfo.width = swpChain->swapChainExtent.width;
		framebufferInfo.height = swpChain->swapChainExtent.height;
		framebufferInfo.layers = 1;

		if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &swpChain->swapChainFrameBuffers[i]) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create framebuffer");
		}
	}
}

void Framebuffers::cleanup(VkDevice &device, std::vector<VkFramebuffer> &swapChainFrameBuffers)
{
	for (auto framebuffer : swapChainFrameBuffers)
	{
		vkDestroyFramebuffer(device, framebuffer, nullptr);
	}
}
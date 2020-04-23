#include "Renderer.hpp"

Renderer::Renderer(std::shared_ptr<VulkanInstance> vkInst)
{
	this->vkInst = vkInst;  
}

void Renderer::mainLoop(GLFWwindow *window)
{
	auto vkInstance = vkInst.lock();
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		drawFrame(vkInstance->deviceManager->imageAvailableSemaphores, vkInstance->deviceManager->renderFinishedSemaphores, vkInstance->deviceManager->currentFrame);
	}

	vkDeviceWaitIdle(vkInstance->deviceManager->device);
}

/*Functions:
	acquire image from swap chain
	execute command buffer with image as attachment in framebuffer
	return image to swap chain */
void Renderer::drawFrame(std::vector<VkSemaphore> &imageAvailableSemaphores, std::vector<VkSemaphore> &renderFinishedSemaphores, size_t &currentFrame)
{
	auto vkInstance = vkInst.lock();
	vkWaitForFences(vkInstance->deviceManager->device, 1, &vkInstance->deviceManager->inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);
	
	uint32_t imageIndex;
	vkAcquireNextImageKHR(vkInstance->deviceManager->device, vkInstance->deviceManager->swapChain, UINT64_MAX,
						  imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

	if(vkInstance->deviceManager->imagesInFlight[imageIndex] != VK_NULL_HANDLE)
	{
		vkWaitForFences(vkInstance->deviceManager->device, 1, &vkInstance->deviceManager->imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
	}

	vkInstance->deviceManager->imagesInFlight[imageIndex] = vkInstance->deviceManager->inFlightFences[currentFrame];

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore waitSemaphores[] = {imageAvailableSemaphores[currentFrame]};
	VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &vkInstance->deviceManager->commandBuffers[imageIndex];

	// set which semaphores to signal once the command buffers finish execution
	VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[vkInstance->deviceManager->currentFrame]};
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	vkResetFences(vkInstance->deviceManager->device, 1, &vkInstance->deviceManager->inFlightFences[currentFrame]);

	if(vkQueueSubmit(vkInstance->deviceManager->graphicsQueue, 1, &submitInfo, vkInstance->deviceManager->inFlightFences[currentFrame]) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to submit draw command buffer");
	}

	VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;

	VkSwapchainKHR swapChains[] = {vkInstance->deviceManager->swapChain};
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;
	presentInfo.pImageIndices = &imageIndex;
	presentInfo.pResults = nullptr; //optional

	vkQueuePresentKHR(vkInstance->deviceManager->presentQueue, &presentInfo);

	currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}
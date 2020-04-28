#include "Renderer.hpp"
#include "ImageViews.hpp"
#include "Framebuffers.hpp"

void Renderer::initRendering()
{
	auto logDev = logicalDevice.lock();
	auto windowSurface = winSurf.lock();

	swpChain->createSwapChain(windowSurface->surface,logDev);
	ImageViews::createImageViews(swpChain, logDev->device);
	rndPass->createRenderPass(swpChain->swapChainImageFormat, logDev->device);
	gPipeline->createGraphicsPipeline(logDev->device,swpChain->swapChainExtent,rndPass->renderPass);
	Framebuffers::createFramebuffers(rndPass->renderPass, logDev->device,swpChain);
	cmdBuffers->createCommandPool(windowSurface->surface);
	cmdBuffers->createCommandBuffers(rndPass->renderPass,gPipeline->graphicsPipeline, swpChain);
	syncObjects->CreateSyncObjects(logDev->device, swpChain->swapChainImages);
}

Renderer::Renderer(std::shared_ptr<VulkanInstance> vulkanInstance, std::shared_ptr<LogicalDevice> logicalDevice, std::shared_ptr<WindowSurface> winSurf)
{
	this->vkInst = vulkanInstance;  
	this->logicalDevice = logicalDevice;
	this->winSurf = winSurf;

	syncObjects = std::make_unique<SyncObjects>();
	swpChain = std::make_unique<SwapChain>();
	rndPass = std::make_unique<RenderPass>();
	gPipeline = std::make_unique<GraphicsPipeline>();
	cmdBuffers = std::make_unique<CommandBuffers>(logicalDevice);
}

void Renderer::mainLoop(GLFWwindow *window)
{
	auto vkInstance = vkInst.lock();
	auto logDev = logicalDevice.lock();
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		drawFrame(syncObjects->imageAvailableSemaphores, syncObjects->renderFinishedSemaphores);
	}

	vkDeviceWaitIdle(logDev->device);
}

/*Functions:
	acquire image from swap chain
	execute command buffer with image as attachment in framebuffer
	return image to swap chain */
void Renderer::drawFrame(std::vector<VkSemaphore> &imageAvailableSemaphores, std::vector<VkSemaphore> &renderFinishedSemaphores)
{
	auto vkInstance = vkInst.lock();
	auto logDev = logicalDevice.lock();
	vkWaitForFences(logDev->device, 1, &syncObjects->inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);
	
	uint32_t imageIndex;
	vkAcquireNextImageKHR(logDev->device, swpChain->swapChain, UINT64_MAX,
						  imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

	if(syncObjects->imagesInFlight[imageIndex] != VK_NULL_HANDLE)
	{
		vkWaitForFences(logDev->device, 1, &syncObjects->imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
	}

	syncObjects->imagesInFlight[imageIndex] = syncObjects->inFlightFences[currentFrame];

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore waitSemaphores[] = {imageAvailableSemaphores[currentFrame]};
	VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &cmdBuffers->commandBuffers[imageIndex];

	// set which semaphores to signal once the command buffers finish execution
	VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[currentFrame]};
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	vkResetFences(logDev->device, 1, &syncObjects->inFlightFences[currentFrame]);

	if(vkQueueSubmit(logDev->graphicsQueue, 1, &submitInfo, syncObjects->inFlightFences[currentFrame]) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to submit draw command buffer");
	}

	VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;

	VkSwapchainKHR swapChains[] = {swpChain->swapChain};
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;
	presentInfo.pImageIndices = &imageIndex;
	presentInfo.pResults = nullptr; //optional

	vkQueuePresentKHR(logDev->presentQueue, &presentInfo);

	currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void Renderer::cleanup()
{
	auto logDev = logicalDevice.lock();

	syncObjects->cleanup(logDev->device);
	cmdBuffers->cleanup();
	Framebuffers::cleanup(logDev->device,swpChain->swapChainFrameBuffers);
	gPipeline->cleanup(logDev->device);
	rndPass->cleanup(logDev->device);
	ImageViews::cleanup(logDev->device,swpChain->swapChainImageViews);
	swpChain->cleanup(logDev->device);
}
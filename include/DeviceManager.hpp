#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <optional>
#include <vector>

const std::vector<const char *> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME};

struct QueueFamilyIndices
{
	//optional because need to see if any value is returned
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete()
	{
		return graphicsFamily.has_value();
	}
};

struct SwapChainSupportDetails
{
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

class DeviceManager
{
public:
	DeviceManager();
	void pickPhysicalDevice(VkInstance &instance, VkSurfaceKHR &surface);
	void createLogicalDevice(VkSurfaceKHR &surface);
	void cleanup();
	bool checkDeviceExtensionSupport(const VkPhysicalDevice &device);
	void createSwapChain(const VkSurfaceKHR &surface);
	void createImageViews();
	void createFramebuffers(const VkRenderPass &renderPass);
	void createCommandPool(VkSurfaceKHR &surface);
	void createCommandBuffers(const VkRenderPass &renderPass, const VkPipeline &graphicsPipeline);
	void CreateSyncObjects();
	VkDevice device;
	VkExtent2D swapChainExtent;
	VkFormat swapChainImageFormat;
	VkSwapchainKHR swapChain;
	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;

	std::vector<VkFence> inFlightFences;
	std::vector<VkFence> imagesInFlight;
	std::vector<VkCommandBuffer> commandBuffers;
	VkQueue graphicsQueue;
	VkQueue presentQueue;
	size_t currentFrame = 0;
private:
	
	
	VkCommandPool commandPool;
	std::vector<VkFramebuffer> swapChainFrameBuffers;
	VkPhysicalDevice physicalDevice;
	
	
	
	std::vector<VkImage> swapChainImages;

	std::vector<VkImageView> swapChainImageViews;

	QueueFamilyIndices findQueueFamilies(const VkPhysicalDevice &device, const VkSurfaceKHR &surface);

	bool isDeviceSuitable(const VkPhysicalDevice &device, const VkSurfaceKHR &surface);
	SwapChainSupportDetails querySwapChainSupport(const VkPhysicalDevice &device, const VkSurfaceKHR &surface);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);

	// Swap extent - resolution of images
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);
};
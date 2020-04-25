#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <optional>
#include <vector>

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

const std::vector<const char *> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME};

class PhysicalDevice
{
public:
	PhysicalDevice();
	void pickPhysicalDevice(VkInstance &instance, VkSurfaceKHR &surface);
	static QueueFamilyIndices findQueueFamilies(const VkPhysicalDevice &device, const VkSurfaceKHR &surface);
	static SwapChainSupportDetails querySwapChainSupport(const VkPhysicalDevice &device, const VkSurfaceKHR &surface);

	VkPhysicalDevice physicalDevice;

	/* Doesn't need cleanup because physical device
		Will be implicitly destroyed when vkInstance is destroyed*/
private:

	static bool checkDeviceExtensionSupport(const VkPhysicalDevice &device);
	static bool isDeviceSuitable(const VkPhysicalDevice &device, const VkSurfaceKHR &surface);
};
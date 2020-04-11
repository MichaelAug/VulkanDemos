#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <optional>

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

class DeviceManager
{
public:
	DeviceManager();
	void pickPhysicalDevice(VkInstance &instance, VkSurfaceKHR &surface);
	void createLogicalDevice(VkSurfaceKHR &surface);
	void cleanup();
	
private:
	VkPhysicalDevice physicalDevice;
	VkDevice device;
	VkQueue graphicsQueue;
	VkQueue presentQueue;


	QueueFamilyIndices findQueueFamilies(const VkPhysicalDevice &device, const VkSurfaceKHR &surface);

	bool isDeviceSuitable(const VkPhysicalDevice &device,const VkSurfaceKHR &surface);
};
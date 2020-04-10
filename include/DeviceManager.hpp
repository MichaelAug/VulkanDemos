#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <optional>

struct QueueFamilyIndices
{
	//optional because need to see if any value is returned
	std::optional<uint32_t> graphicsFamily;

	bool isComplete()
	{
		return graphicsFamily.has_value();
	}
};

class DeviceManager
{
public:
	DeviceManager();
	void pickPhysicalDevice(VkInstance &instance);
	void createLogicalDevice();
	void cleanup();
	
private:
	VkPhysicalDevice physicalDevice;
	VkDevice device;
	VkQueue graphicsQueue;

	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

	bool isDeviceSuitable(VkPhysicalDevice device);
};
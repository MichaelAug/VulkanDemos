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
	void pickPhysicalDevice(VkInstance &instance);

private:

	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

	bool isDeviceSuitable(VkPhysicalDevice device);
};
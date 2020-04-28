#pragma once
#include <memory>
#include "PhysicalDevice.hpp"

class LogicalDevice
{
public:
	LogicalDevice();
	VkPhysicalDevice &getPhysicalDevice();
	void createDevice(VkInstance &instance, VkSurfaceKHR &surface);
	void cleanup();

	VkDevice device;
	VkQueue graphicsQueue;
	VkQueue presentQueue;
private:
	void createLogicalDevice(VkSurfaceKHR &surface);
	std::unique_ptr<PhysicalDevice> physDev;
};
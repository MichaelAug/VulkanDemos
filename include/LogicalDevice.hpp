#pragma once
#include <memory>
#include "PhysicalDevice.hpp"

class LogicalDevice
{
public:
	LogicalDevice();
	VkPhysicalDevice &getPhysicalDevice();
	void createDevice(VkInstance &instance, VkSurfaceKHR &surface);
	void createLogicalDevice(VkSurfaceKHR &surface);
	void cleanup();

	VkDevice device;
	VkQueue graphicsQueue;
	VkQueue presentQueue;
private:
	std::unique_ptr<PhysicalDevice> physDev;
};
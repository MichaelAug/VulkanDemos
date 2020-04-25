#include "LogicalDevice.hpp"
#include <set>
#include "ValidationLayers.hpp"

LogicalDevice::LogicalDevice()
{
	physDev = std::make_unique<PhysicalDevice>();
}

void LogicalDevice::createDevice(VkInstance &instance, VkSurfaceKHR &surface)
{
	// Have to pick physical device first
	physDev->pickPhysicalDevice(instance, surface);

	createLogicalDevice(surface);
}

void LogicalDevice::cleanup()
{
	vkDestroyDevice(device, nullptr);
}

VkPhysicalDevice &LogicalDevice::getPhysicalDevice()
{
	return physDev->physicalDevice;
}

void LogicalDevice::createLogicalDevice(VkSurfaceKHR &surface)
{
	QueueFamilyIndices indices = physDev->findQueueFamilies(physDev->physicalDevice, surface);

	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(),
											  indices.presentFamily.value()};

	float queuePriority = 1.0f;
	for (uint32_t queueFamily : uniqueQueueFamilies)
	{
		VkDeviceQueueCreateInfo queueCreateInfo = {};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		queueCreateInfos.push_back(queueCreateInfo);
	}

	//TODO: specify device features
	VkPhysicalDeviceFeatures deviceFeatures = {};

	VkDeviceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
	createInfo.pQueueCreateInfos = queueCreateInfos.data();

	createInfo.pEnabledFeatures = &deviceFeatures;

	createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
	createInfo.ppEnabledExtensionNames = deviceExtensions.data();

	if (enableValidationLayers)
	{
		/*enabledLayerCount and ppEnabledLayerNames are ignored by up-to-date implementations
		 but it's still good to set them to be compatible with older versions*/
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();
	}
	else
	{
		createInfo.enabledLayerCount = 0;
	}

	if (vkCreateDevice(physDev->physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create logical device");
	}

	vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
	vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);
}
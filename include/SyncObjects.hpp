#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>

// How many frames should the program process concurrently
const int MAX_FRAMES_IN_FLIGHT = 2;

class SyncObjects
{
public:

	void CreateSyncObjects(VkDevice &device,std::vector<VkImage> &swapChainImages);
	void cleanup(VkDevice &device);

	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;

	std::vector<VkFence> inFlightFences;
	std::vector<VkFence> imagesInFlight;
private:

};
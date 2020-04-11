#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class WindowSurface
{
public:
	void createSurface(VkInstance &instance, GLFWwindow *window);
	void cleanup(VkInstance &instance);

	VkSurfaceKHR surface;

private:
};
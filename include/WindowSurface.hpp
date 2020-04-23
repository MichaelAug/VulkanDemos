#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class WindowSurface
{
public:
	void createSurface(VkInstance &instance);
	void cleanup(VkInstance &instance);
	void InitWindow();

	VkSurfaceKHR surface;
    GLFWwindow *window;
private:
};
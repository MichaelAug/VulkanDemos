#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class WindowSurface
{
public:
	void createSurface(VkInstance &instance);
	void cleanup();
	void InitWindow();
	void destroyInstance(VkInstance &instance);

	VkSurfaceKHR surface;
	GLFWwindow *window;
	bool framebufferResized = false;

private:
	const char *windowTitle = "Vulkan";

	static void framebufferResizeCallback(GLFWwindow *window, int width, int height);
};
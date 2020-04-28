#include "WindowSurface.hpp"
#include <stdexcept>

void WindowSurface::createSurface(VkInstance &instance)
{
	if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create window surface");
	}
}

void WindowSurface::cleanup()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void WindowSurface::InitWindow()
{
	// Init GLFW library
	glfwInit();

	// Tell GLFW not to create OpenGL context
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	// Disable screen resizing (can't handle resizable windows for now)
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	//parameters: width, height, title, monitor, OpenGL parameter
	window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}

void WindowSurface::destroyInstance(VkInstance &instance)
{
	vkDestroySurfaceKHR(instance, surface, nullptr);
}
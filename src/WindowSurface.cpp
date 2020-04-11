#include "WindowSurface.hpp"
#include <stdexcept>

void WindowSurface::createSurface(VkInstance &instance, GLFWwindow *window)
{
	if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create window surface");
	}
}

void WindowSurface::cleanup(VkInstance &instance)
{
	vkDestroySurfaceKHR(instance, surface, nullptr);
}
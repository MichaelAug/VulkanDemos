#include "WindowSurface.hpp"
#include <stdexcept>

void WindowSurface::framebufferResizeCallback(GLFWwindow *window, int width, int height)
{
	auto app = reinterpret_cast<WindowSurface *>(glfwGetWindowUserPointer(window));
	app->framebufferResized = true;
}

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

	// Enable screen resizing
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	//parameters: width, height, title, monitor, OpenGL parameter
	window = glfwCreateWindow(WIDTH, HEIGHT, windowTitle, nullptr, nullptr);

	glfwSetWindowUserPointer(window, this);

	glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

void WindowSurface::destroyInstance(VkInstance &instance)
{
	vkDestroySurfaceKHR(instance, surface, nullptr);
}
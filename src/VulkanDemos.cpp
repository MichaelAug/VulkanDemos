#include "VulkanDemos.hpp"
#include "VulkanInstance.hpp"

VulkanDemos::VulkanDemos()
{
	vkInstance = std::make_unique<VulkanInstance>();
}

void VulkanDemos::InitWindow()
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

void VulkanDemos::mainLoop()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}
}

void VulkanDemos::cleanup()
{
	vkInstance->cleanup();

	glfwDestroyWindow(window);

	glfwTerminate();
}
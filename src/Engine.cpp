#include "Engine.hpp"
#include "VulkanInstance.hpp"

void Engine::run()
{
	windowSurface->InitWindow();
	vkInstance->initVulkan();

	renderer->mainLoop(windowSurface->window);

	cleanup();
}

Engine::Engine()
{
	windowSurface = std::make_shared<WindowSurface>();
	logicalDevice = std::make_shared<LogicalDevice>();
	vkInstance = std::make_shared<VulkanInstance>(windowSurface, logicalDevice);
	renderer = std::make_shared<Renderer>(vkInstance, logicalDevice);
}

void Engine::cleanup()
{
	vkInstance->cleanup();
}


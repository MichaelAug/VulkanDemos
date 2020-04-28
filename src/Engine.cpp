#include "Engine.hpp"
#include "VulkanInstance.hpp"

void Engine::Init()
{
	//Order of calls matters
	windowSurface->InitWindow();

	vkInstance->initVulkan();

	windowSurface->createSurface(vkInstance->instance);

	logicalDevice->createDevice(vkInstance->instance, windowSurface->surface);

	renderer->initRendering();
}

void Engine::run()
{
	Init();

	renderer->mainLoop(windowSurface->window);

	cleanup();
}

Engine::Engine()
{
	windowSurface = std::make_shared<WindowSurface>();
	logicalDevice = std::make_shared<LogicalDevice>();
	vkInstance = std::make_shared<VulkanInstance>();
	renderer = std::make_shared<Renderer>(vkInstance, logicalDevice, windowSurface);
}

void Engine::cleanup()
{
	//Order of calls matters
	renderer->cleanup();
	logicalDevice->cleanup();
	windowSurface->destroyInstance(vkInstance->instance);
	vkInstance->cleanup();
	windowSurface->cleanup();
}

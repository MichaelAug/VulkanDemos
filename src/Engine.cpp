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
	vkInstance = std::make_shared<VulkanInstance>(windowSurface);
	renderer = std::make_shared<Renderer>(vkInstance);
}

void Engine::cleanup()
{
	vkInstance->cleanup();
}


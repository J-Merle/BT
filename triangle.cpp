#include "vulkan/vulkan.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_vulkan.h"

#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>

class HelloTriangleApplication {
	
	public:
		void run() {
			initWindow();
			initVulkan();
			mainLoop();
			cleanup();
		}

	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Event event;
		VkInstance instance;

		void initWindow() {
			window = SDL_CreateWindow("Triangle", SDL_WINDOWPOS_UNDEFINED,  SDL_WINDOWPOS_UNDEFINED, 400, 400, SDL_WINDOW_OPENGL);
			renderer = SDL_CreateRenderer(window, -1, 0);
		}

		void initVulkan() {
			createInstance();
		}

		void mainLoop() {
			while(1) {
				if(SDL_PollEvent(&event)) {
					if(event.type == SDL_QUIT) {
						break;
					}
				} 
				SDL_RenderClear(renderer);
				SDL_RenderPresent(renderer);
			}

			cleanup();
		}

		void cleanup() {
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
		}

		void createInstance() {
			VkApplicationInfo appInfo = {};
			appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			appInfo.pApplicationName = "Blanco Tower";
			appInfo.applicationVersion = VK_MAKE_VERSION(1,0,0);
			appInfo.pEngineName = "No Engine";
			appInfo.engineVersion = VK_MAKE_VERSION(1,0,0);
			appInfo.apiVersion = VK_API_VERSION_1_2;

			VkInstanceCreateInfo createInfo = {};
			createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			createInfo.pApplicationInfo = &appInfo;

			unsigned int count;
			if(! SDL_Vulkan_GetInstanceExtensions(window, &count, nullptr))
				std::cerr << "Could not retrieve Vulkan Instance" << std::endl;

		}
};

int main() {
	HelloTriangleApplication app;

	try{
		app.run();
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}


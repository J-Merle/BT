#include "vulkan/vulkan.h"
#include "SDL2/SDL.h"

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


		void initWindow() {
			window = SDL_CreateWindow("Triangle", SDL_WINDOWPOS_UNDEFINED,  SDL_WINDOWPOS_UNDEFINED, 400, 400, SDL_WINDOW_OPENGL);
			renderer = SDL_CreateRenderer(window, -1, 0);
		}

		void initVulkan() {
		
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


#include <stdio.h>
#include "vulkan/vulkan.h"
#include "SDL2/SDL.h"

using namespace std;

int main(int argc, char* argv[])
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(
			"App test",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			600,
			400,
			SDL_WINDOW_OPENGL
	);

	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	while(1) {
		if (SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
				break;
			} else if (event.type == SDL_KEYDOWN) {
				SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
			}
		}
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}
	

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}

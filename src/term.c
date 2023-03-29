#include <SDL2/SDL.h>
#include <stdlib.h>



int main() {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
	printf("SDL initialization failed: %s\n", SDL_GetError());
	exit(EXIT_FAILURE);
    };

    SDL_Window *window = SDL_CreateWindow("My Window",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        640, 480, SDL_WINDOW_SHOWN);

    if (!window) {
	printf("Window creation failed: %s\n", SDL_GetError());
	return 1;
    }
	









    SDL_Quit();
}

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FONT_SIZE 24

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    TTF_Font* font = NULL;
    SDL_Texture* texture = NULL;
    SDL_Surface* surface = NULL;
    SDL_Event event;
    int quit = 0;
    char message[256] = ""; // message buffer
    int message_length = 0; // length of message buffer
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() < 0) {
        fprintf(stderr, "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Termu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    font = TTF_OpenFont("/Users/ahmad/Library/Fonts/Hack-Bold.ttf", FONT_SIZE);
    if (font == NULL) {
        fprintf(stderr, "Font could not be loaded! SDL_ttf Error: %s\n", TTF_GetError());
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
            else if (event.type == SDL_TEXTINPUT) { // if text input event
                if (message_length + strlen(event.text.text) < 256) { // if message buffer not full
                    strcat(message, event.text.text); // append new text to message buffer
                    message_length += strlen(event.text.text); // update message buffer length
                }
            }
        }

        SDL_RenderClear(renderer); // clear screen

        surface = TTF_RenderText_Solid(font, message, (SDL_Color) {0xFF, 0xFF, 0xFF, 0xFF}); // create surface with message text
        texture = SDL_CreateTextureFromSurface(renderer, surface); // create texture from surface
        SDL_FreeSurface(surface); // free surface
        SDL_RenderCopy(renderer, texture, NULL, &(SDL_Rect) {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}); // copy texture to renderer
        SDL_DestroyTexture(texture); // destroy texture

        SDL_RenderPresent(renderer); // update screen
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}


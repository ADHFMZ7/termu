#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_keycode.h>
#include <stdio.h>
#include <string.h>

#define FONT_SIZE 14 
#define SCREEN_WIDTH 80*FONT_SIZE
#define SCREEN_HEIGHT 15*FONT_SIZE*3
#define BUFSIZE (SCREEN_WIDTH/FONT_SIZE) * (SCREEN_HEIGHT/FONT_SIZE)

#define FONT_NAME "/Users/ahmad/Library/Fonts/Roboto Mono Medium for Powerline.ttf"

TTF_Font *create_font(char *font_name, int font_size) {
    TTF_Font *font;
    if ((font = TTF_OpenFont(font_name, font_size)) == NULL) {
        fprintf(stderr, "Font could not be loaded! SDL_ttf Error: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    TTF_SetFontHinting(font, TTF_HINTING_NORMAL);
    return font;
}

char *init_buffer(int width, int height) {

    char *buffer = (char *) malloc(height * ( width + 1));

    for (int i = 0; i < height; i++ ) {
        for (int j = 1; j < width + 1; j++) {
            if (j == width) {
                buffer[(i * width) + j] = '\n';
                printf("Printed newline number %d\n", j);
            }
            else {
                buffer[(i * width) + j] = ' ';
            }
        }
    }
    buffer[height * (width + 1) - 1] = '\0';



    // for (int i = 0; i < height; i++ ) {
    //     for (int j = 0; j < width; j++) {
    //         buffer[(i * width) + j] = '-';
    //     }
    //     buffer[(i * width) + width] = '\n';
    // }
    // buffer[height * (width + 1) - 1] = '\0';
    return buffer;
}


int main() {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* texture = NULL;
    SDL_Surface* surface = NULL;
    SDL_Event event;
    int quit = 0;
    char *message = init_buffer(80, 15); // message buffer
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

    TTF_Font* font = create_font(FONT_NAME, FONT_SIZE);


    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE) {
                printf("%s\n", message);
                if (message_length <= 0) {
                    printf("\a");
                    continue;
                }
                //message[message_length - 2] = '\0';
                message[--message_length] = ' ';
            }
            else if (event.type == SDL_TEXTINPUT) { // if text input event
                if (message_length + strlen(event.text.text) < BUFSIZE) { // if message buffer not full
                    message[message_length++] = event.text.text[0]; // append new text to message buffer
                    //message_length += strlen(event.text.text); // update message buffer length
                    printf("%s\n", message);
                }
            }
        }

        SDL_RenderClear(renderer); // clear screen

        surface = TTF_RenderUTF8_Blended_Wrapped(font, message, (SDL_Color) {0xFF, 0xFF, 0xFF, 0xFF}, SCREEN_WIDTH); // create surface with message text
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

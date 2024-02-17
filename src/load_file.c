#include "../dependencies/maze.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>


SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer) {
    SDL_Texture *newTexture = IMG_LoadTexture(renderer, path);
    if (newTexture == NULL) {
        printf("Failed to load texture image! SDL_image Error: %s\n", IMG_GetError());
    }
    return newTexture;
}

#include "../dependencies/maze.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>


/**
 * loadTexture - Load a texture from a file
 * @path: The path to the image file
 * @renderer: The renderer to load the texture onto
 *
 * Return: The loaded texture
 */
SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer) {
    SDL_Texture *newTexture = IMG_LoadTexture(renderer, path);
    if (newTexture == NULL) {
        printf("Failed to load texture image! SDL_image Error: %s\n", IMG_GetError());
    }
    return newTexture;
}

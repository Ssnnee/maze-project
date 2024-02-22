#include "../dependencies/maze.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>


float px,py,pdx,pdy,pa;



/**
 * main - Entry point
 *
 * Return: 0 on success, anything else on failure
 */
int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("3D Maze Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("Failed to initialize SDL_image: %s\n", IMG_GetError());
        return  1;
    }

    px=150; py=400; pa=90;
    pdx=cos(degToRad(pa)); pdy=-sin(degToRad(pa));

    if(!loadMedia(renderer))
        return 1;

    SDL_Event event;
    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN)
            {
                Buttons(event);
            }
        }

        SDL_SetRenderDrawColor(renderer, 0x33, 0x33, 0x33, 0xFF);
        SDL_RenderClear(renderer);

        drawMap2D(renderer);
        drawPlayer2D(renderer);
        drawRays2D(renderer);

        SDL_RenderPresent(renderer);
    }
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

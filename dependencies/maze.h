#ifndef MAZE_H
#define MAZE_H


#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

#define M_PI 3.14159265358979323846
#define mapX  8      //map width
#define mapY  8      //map height
#define mapS 62      //map cube size

typedef struct {
    int w, a, d, s;  // Button state: on/off
} ButtonKeys;

typedef struct {
    int type;         // Sprite type: static, key, enemy
    int state;        // Sprite state: on/off
    int map;          // Texture to show
    float x, y, z;    // Position
} Sprite;

void init();
void display();
void ButtonDown(unsigned char key, int x, int y);
void ButtonUp(unsigned char key, int x, int y);
void resize(int w, int h);
SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer);
bool loadMedia(SDL_Renderer* renderer);
float degToRad(int a);
void Buttons(SDL_Event event);
void drawMap2D(SDL_Renderer* renderer);
void drawPlayer2D(SDL_Renderer* renderer);
void drawRays2D(SDL_Renderer* renderer);

extern float px,py,pdx,pdy,pa;



#endif

#include "../dependencies/maze.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <math.h>

SDL_Texture* wallTexture = NULL;
SDL_Texture* skyTexture = NULL;

//------------------------------MAP----------------------------------------------
int map[]=           //the map array. Edit to change level but keep the outer walls
{
    1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,1,
    1,0,1,1,1,1,0,1,
    1,0,1,0,0,0,0,1,
    1,0,1,0,1,1,0,1,
    1,0,0,0,0,1,0,1,
    1,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,
};

void drawMap2D(SDL_Renderer* renderer)
{
    int x,y,xo,yo;
    for(y=0;y<mapY;y++)
    {
        for(x=0;x<mapX;x++)
        {
            if(map[y*mapX+x]==1)
             SDL_SetRenderDrawColor(renderer, 111, 255, 255, 155);
            else
             SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

            xo = x * mapS;
            yo = y * mapS;
            SDL_Rect rect = {xo+2, yo+1, mapS-2, mapS-2};
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

//------------------------PLAYER------------------------------------------------
float degToRad(int a) { return a*M_PI/180.0;}
int FixAng(int a){ if(a>359){ a-=360;} if(a<0){ a+=360;} return a;}


void drawPlayer2D(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawPoint(renderer, px, py);
    SDL_RenderDrawLine(renderer, px, py, px+pdx*20, py+pdy*20);
}

void Buttons(SDL_Event event)
{
    switch (event.key.keysym.sym)
    {
        case SDLK_h:
            pa+=5;
            pa=FixAng(pa);
            pdx=cos(degToRad(pa));
            pdy=-sin(degToRad(pa));
            break;
        case SDLK_l:
            pa-=5;
            pa=FixAng(pa);
            pdx=cos(degToRad(pa));
            pdy=-sin(degToRad(pa));
            break;
        case SDLK_k:
            if (map[(int)(py + pdy * 5) / mapS * mapX + (int)(px + pdx * 5) / mapS] == 0) {
                px+=pdx*5;
                py+=pdy*5;
            }
            break;
        case SDLK_j:
            if (map[(int)(py - pdy * 5) / mapS * mapX + (int)(px - pdx * 5) / mapS] == 0) {
                px-=pdx*5;
                py-=pdy*5;
            }
            break;
        default:
            break;
    }
}


//---------------------------Draw Rays and Walls--------------------------------
float distance(int ax, int ay, int bx,int by,int  ang)
{ return cos(degToRad(ang))*(bx-ax)-sin(degToRad(ang))*(by-ay);}

bool loadMedia(SDL_Renderer* renderer) {
    bool success = true;

    wallTexture = loadTexture("./textures/redbrick.bmp", renderer);
    skyTexture = loadTexture("./textures/sky.bmp", renderer);

    if (wallTexture == NULL || skyTexture == NULL) {
        success = false;
    }

    return success;
}


void drawRays2D(SDL_Renderer* renderer)
{
    int r,mx,my,mp,dof; float vx,vy,rx,ry,ra,xo,yo,disV,disH;

    ra=FixAng(pa+30);                                                              //ray set back 30 degrees

    for(r=0;r<60;r++)
    {
        //---Vertical---
        dof=0; disV=100000;
        float Tan=tan(degToRad(ra));
        if(cos(degToRad(ra))> 0.001){ rx=(((int)px>>6)<<6)+64;      ry=(px-rx)*Tan+py; xo= 64; yo=-xo*Tan;}//looking left
        else if(cos(degToRad(ra))<-0.001){ rx=(((int)px>>6)<<6) -0.0001; ry=(px-rx)*Tan+py; xo=-64; yo=-xo*Tan;}//looking right
        else { rx=px; ry=py; dof=8;}                                                  //looking up or down. no hit

        while(dof<8)
        {
            mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;
            if(mp>0 && mp<mapX*mapY && map[mp]==1){ dof=8; disV=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py);}//hit
            else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
        }
        vx=rx; vy=ry;

        //---Horizontal---
        dof=0; disH=100000;
        Tan=1.0/Tan;
        if(sin(degToRad(ra))> 0.001){ ry=(((int)py>>6)<<6) -0.0001; rx=(py-ry)*Tan+px; yo=-64; xo=-yo*Tan;}//looking up
        else if(sin(degToRad(ra))<-0.001){ ry=(((int)py>>6)<<6)+64;      rx=(py-ry)*Tan+px; yo= 64; xo=-yo*Tan;}//looking down
        else{ rx=px; ry=py; dof=8;}                                                   //looking straight left or right

        while(dof<8)
        {
            mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;
            if(mp>0 && mp<mapX*mapY && map[mp]==1){ dof=8; disH=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py);}//hit
            else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
        }

        SDL_SetRenderDrawColor(renderer, 0, 8, 0, 255);
        if(disV<disH){ rx=vx; ry=vy; disH=disV; SDL_SetRenderDrawColor(renderer, 0, 6, 0, 255);}                  //horizontal hit first
        SDL_RenderDrawLine(renderer, px, py, rx, ry);//draw 2D ray

        int ca=FixAng(pa-ra); disH=disH*cos(degToRad(ca));                            //fix fisheye
        int lineH = (mapS*320)/(disH); if(lineH>320){ lineH=320;}                     //line height and limit
        int lineOff = 160 - (lineH>>1);                                               //line offset
                                                                                      //
                                                                                      // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                                                                                      // SDL_RenderDrawLine(renderer, r*8+530, lineOff, r*8+530, lineOff+lineH );//draw vertical wall

                                                                                      // Inside the drawRays2D function
                                                                                      // Draw walls using textures
        SDL_Rect wallRect = {r * 8 + 530, lineOff, 8, lineH};
        SDL_RenderCopy(renderer, wallTexture, NULL, &wallRect);

        // Inside the main function, after drawing the sky
        // Render sky
        // SDL_Rect skyRect = {900, 0, 200, 20}; // Assuming sky height is 255 pixels
        // SDL_RenderCopy(renderer, skyTexture, NULL, &skyRect);

        ra=FixAng(ra-1);                                                              //go to next ray
    }
}

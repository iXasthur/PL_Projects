//
//  main.cpp
//  L10_1
//
//  Created by Михаил Ковалевский on 27.11.2019.
//  Copyright © 2019 Михаил Ковалевский. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <SDL2/SDL.h>

int WIDTH = 800, HEIGHT = 600;
const int FRAMES_PER_SECOND = 30;

int check_window(SDL_Window *window){
    if ( window == NULL )
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return 1;
    } else {
        printf( "Window has been created(%dx%d)!\n", WIDTH, HEIGHT);
        return 0;
    }
}




void CenterSquareChange(SDL_Renderer *renderer, SDL_Rect &cRect, int cRectLength, int moveX, int moveY){
    cRect.x = WIDTH/2 - cRectLength + moveX;
    cRect.y = HEIGHT/2 - cRectLength + moveY;
    cRect.w = (WIDTH/2 - cRect.x + moveX)*2;
    cRect.h = cRect.w;
}




void dashLine(SDL_Renderer *renderer, int x1, int y1, int x2, int y2){
    float x, y;
    int count;
    printf("\nx1 = %d y1 = %d x2 = %d y2 = %d\n",x1,y1,x2,y2);
    
    
    if(abs(x2-x1) > abs(y2-y1)){
        for(x=x1 ;x<x2 ;x+=10){
            for(count=0;count<15 && x<x2;count++){
                x++;
                y=(x-x1)/(x2-x1)*(y2-y1)+y1;
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    } else {
        if(y1<y2){
                for(y=y1 ;y<y2 ;y+=10){
                    for(count=0;count<15 && y<y2;count++){
                        y++;
                        x=(y-y1)*(x2-x1)/(y2-y1)+x1;
                        SDL_RenderDrawPoint(renderer, x, y);
                    }
                }
        } else {
            for(y=y1 ;y>y2 ;y-=10){
                for(count=0;count<15 && y>y2;count++){
                    y--;
                    x=(y-y1)*(x2-x1)/(y2-y1)+x1;
                    SDL_RenderDrawPoint(renderer, x, y);
                }
            }
        }
    }
}



void drawstar(SDL_Renderer *renderer, SDL_Rect &cRect, float &rot, int moveStarX, int moveStarY, int starSize){
    int x1, y1, x2, y2;
    float f=0;
    float r=500 + starSize;
    int kw=0;
    
    static int q1=0, q2=0, q3=0;
    
    for(int i=0;i<5;i++){
        x1=r*cos(f+rot)+moveStarX+WIDTH/2;
        y1=r*sin(f+rot)+moveStarY+HEIGHT/2;
        x2=r*cos(f+rot+6.28/5*2)+moveStarX+WIDTH/2;
        y2=r*sin(f+rot+6.28/5*2)+moveStarY+HEIGHT/2;
        
        q1+=60;
        if(q1>=240){
            q1=60*3;
        }
        q2+=50;
        if(q2>=250){
            q1=50*4;
        }
        q3+=40;
        if(q3>=160){
            q1=40*4;
        }
        SDL_SetRenderDrawColor(renderer, q1, q2, q3, 255);
        
        
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
        f+=6.28/5;
    }
    
    f=0;
    for(int i=0;i<5;i++){
        x1=r*cos(f+rot)+moveStarX+WIDTH/2;
        y1=r*sin(f+rot)+moveStarY+HEIGHT/2;
        x2=r*cos(f+rot+6.28/5*2)+moveStarX+WIDTH/2;
        y2=r*sin(f+rot+6.28/5*2)+moveStarY+HEIGHT/2;
        if(SDL_IntersectRectAndLine(&cRect, &x1, &y1, &x2, &y2)){
//            printf("\nx1 = %d y1 = %d x2 = %d y2 = %d\n",x1,y1,x2,y2);
            if(kw==0){
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(renderer, &cRect);
                SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
                SDL_RenderDrawRect(renderer, &cRect);
                kw=1;
            }
            SDL_SetRenderDrawColor(renderer, 0, 255, 255, 130);
            if(x1<x2){
                dashLine(renderer, x1, y1, x2, y2);
            } else {
                dashLine(renderer, x2, y2, x1, y1);
            }
        }
        f+=6.28/5;
    }
}





int main(int argc, char *argv[])
{
    SDL_Init( SDL_INIT_VIDEO );
    
    SDL_Window *window;
    
    window = SDL_CreateWindow(
                              "^_^",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              WIDTH,
                              HEIGHT,
                              SDL_WINDOW_ALLOW_HIGHDPI
                              );
    
    // Check that the window was successfully created
    if(check_window(window)==1){
        return 0;
    };
    
    WIDTH*=2;
    HEIGHT*=2;
    
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    
    SDL_Event windowEvent;
    
    int kw=0;
    int cRectLength = 200;
    int moveX=0, moveY=0;
    int moveStarX=0 , moveStarY=0;
    int starSize = 0;
    float rot = 0;
    
    
    SDL_Rect cRect;
    cRect.x = WIDTH/2 - cRectLength;
    cRect.y = HEIGHT/2 - cRectLength;
    cRect.w = (WIDTH/2 - cRect.x)*2;
    cRect.h = cRect.w;
    
    
    
//    SDL_Surface *rectSurf;
    // clear window
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    Uint32 start;
    while ( true )
    {
        if ( SDL_PollEvent( &windowEvent ) )
        {
            if ( SDL_QUIT == windowEvent.type )
            {
                break;
            }
            
            if (SDL_KEYDOWN){
                switch (windowEvent.key.keysym.sym)
                {
                    case SDLK_x: {
                        cRectLength+=10;
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        SDL_RenderClear(renderer);
                        CenterSquareChange(renderer, cRect, cRectLength, moveX, moveY);
                        kw=0;
                        break;
                    }
                        
                    case SDLK_z: {
                        cRectLength-=10;
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        SDL_RenderClear(renderer);
                        CenterSquareChange(renderer, cRect, cRectLength, moveX, moveY);
                        kw=0;
                        break;
                    }
                        
                    case SDLK_w: {
                        moveY-=10;
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        SDL_RenderClear(renderer);
                        CenterSquareChange(renderer, cRect, cRectLength, moveX, moveY);
                        kw=0;
                        break;
                    }
                        
                    case SDLK_s: {
                        moveY+=10;
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        SDL_RenderClear(renderer);
                        CenterSquareChange(renderer, cRect, cRectLength, moveX, moveY);
                        kw=0;
                        break;
                    }
                        
                    case SDLK_a: {
                        moveX-=10;
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        SDL_RenderClear(renderer);
                        CenterSquareChange(renderer, cRect, cRectLength, moveX, moveY);
                        kw=0;
                        break;
                    }
                        
                    case SDLK_d: {
                        moveX+=10;
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        SDL_RenderClear(renderer);
                        CenterSquareChange(renderer, cRect, cRectLength, moveX, moveY);
                        kw=0;
                        break;
                    }
                        
                    case SDLK_COMMA: {
                        rot-=0.05;
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        SDL_RenderClear(renderer);
                        drawstar(renderer, cRect, rot, moveStarX, moveStarY, starSize);
                        kw=0;
                        break;
                    }
                        
                    case SDLK_PERIOD: {
                        rot+=0.05;
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        SDL_RenderClear(renderer);
                        drawstar(renderer, cRect, rot, moveStarX, moveStarY, starSize);
                        kw=0;
                        break;
                    }
                        
                    case SDLK_RIGHT: {
                        moveStarX+=10;
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        SDL_RenderClear(renderer);
                        drawstar(renderer, cRect, rot, moveStarX, moveStarY,starSize);
                        kw=0;
                        break;
                    }
                        
                    case SDLK_LEFT: {
                        moveStarX-=10;
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        SDL_RenderClear(renderer);
                        drawstar(renderer, cRect, rot, moveStarX, moveStarY, starSize);
                        kw=0;
                        break;
                    }
                        
                    case SDLK_UP: {
                        moveStarY-=10;
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        SDL_RenderClear(renderer);
                        drawstar(renderer, cRect, rot, moveStarX, moveStarY, starSize);
                        kw=0;
                        break;
                    }
                        
                    case SDLK_DOWN: {
                        moveStarY+=10;
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        SDL_RenderClear(renderer);
                        drawstar(renderer, cRect, rot, moveStarX, moveStarY, starSize);
                        kw=0;
                        break;
                    }
                        
                    case SDLK_LEFTBRACKET: {
                        starSize-=10;
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        SDL_RenderClear(renderer);
                        drawstar(renderer, cRect, rot, moveStarX, moveStarY, starSize);
                        kw=0;
                        break;
                    }
                    
                    case SDLK_RIGHTBRACKET: {
                        starSize+=10;
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        SDL_RenderClear(renderer);
                        drawstar(renderer, cRect, rot, moveStarX, moveStarY, starSize);
                        kw=0;
                        break;
                    }
                }
            }
        }
        
        
        // render window
        start = SDL_GetTicks();
        if(kw==0){
            SDL_SetRenderDrawColor(renderer, 70, 70, 70, 255);
            SDL_RenderDrawRect(renderer, &cRect);
            drawstar(renderer, cRect, rot, moveStarX, moveStarY, starSize);
            SDL_RenderPresent(renderer);
            kw=1;
        }
        Uint32 ticks = SDL_GetTicks();
        if (1000 / FRAMES_PER_SECOND > ticks - start) {
            SDL_Delay(1000 / FRAMES_PER_SECOND - (ticks - start));
        }
    }
    
    
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return EXIT_SUCCESS;
}







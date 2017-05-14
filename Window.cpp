//
// Created by max on 20.05.16.
//

#include <random>
#include <iostream>
#include "Application.h"
#include "Window.h"
#include <SDL2/SDL_image.h>


Window::~Window() {
    SDL_FreeSurface(img);
    SDL_DestroyTexture(tex);
}

Window::Window(const char* title) : SimpleWindow(title, sQuadre * size, sQuadre * size),
                                    rnd() {
    initTexture();
    initRects();
    randomize();
    draw();
    show();
}

int Window::Message(const char * title,const char * message, Uint32 flags = SDL_MESSAGEBOX_INFORMATION) {
    return SDL_ShowSimpleMessageBox(
        flags,
        title,
        message,
        handle()
    );
}

void Window::initTexture() {
    const char tex_file[] = "./numbs.bmp";

    img = SDL_LoadBMP(tex_file);
    if(!img) {
        Message("Load image fail", SDL_GetError(), SDL_MESSAGEBOX_ERROR);
        Application::instance()->quit(2);
        return;
    }
    SDL_SetWindowIcon(handle(), img);
    //tex = SDL_CreateTextureFromSurface(render(), img);
    tex = IMG_LoadTexture(render(), tex_file);
}
void Window::initRects() {
    for(int i=1; i<size*size; ++i) {
        rnum[i-1].h = sQuadre;
        rnum[i-1].w = sQuadre;
        rnum[i-1].x = (i%size)*sQuadre;
        rnum[i-1].y = (i/size)*sQuadre;
    }
    rnum[15].h = sQuadre;
    rnum[15].w = sQuadre;
    rnum[15].x = 0;
    rnum[15].y = 0;
}

void Window::randomize() {
    int i, j;
    int num = 0;

    for (i=0; i<size; ++i)
        for (j=0; j<size; ++j)
            numbs[i][j]=-1;
    do {
        i = rnd() % size;
        j = rnd() % size;
        if(numbs[i][j] == -1) {
            numbs[i][j]=num;
            ++num;
        }
    }
    while(num<16);
}

void Window::move(int x, int y) {
    if(numbs[x][y] == empty)
        return;
    for(int i = x-1; i<=x+1; ++i) {
        if(i<0) continue;
        if(i>=size) continue;
        for(int j = y-1; j<=y+1; ++j) {
            if(j<0) continue;
            if(j>=size) continue;
            if(abs(x-i) == abs(y-j)) continue;
            if(numbs[i][j] == empty) {
                numbs[i][j] = numbs[x][y];
                numbs[x][y] = empty;
                return;
            }
        }
    }
}

bool Window::game() {
    int num = 0;
    int i,j;
    for (i=0; i<size; ++i)
        for (j=0; j<size; ++j) {
            if(numbs[i][j]!=num)
                return true;
            ++num;
        }
    return false;
}

void Window::draw() {
    SDL_Rect rc = {0, 0, sQuadre, sQuadre};
    SDL_SetRenderDrawColor(render(), 255, 255, 255, 255);
    SDL_RenderClear(render());

    for(int i=0; i<size; ++i) {
        rc.x = sQuadre*i;
        for(int j=0; j<size; ++j) {
            rc.y = sQuadre*j;
            SDL_RenderCopy(render(),tex, &rnum[numbs[i][j]], &rc);
        }
    }
    SDL_RenderPresent(render());
}

bool Window::processEvent(const SDL_Event* event) {
    bool result = false;

    switch(event->type) {
        case SDL_WINDOWEVENT:
            if(windowID() == event->window.windowID) {
                switch(event->window.event) {
                    case SDL_WINDOWEVENT_EXPOSED:
                        draw();
                        break;
                    default:
                        break;
                }
                result = true;
            }
            break;
        case SDL_KEYDOWN:
            if(windowID() == event->key.windowID)
            switch(event->key.keysym.sym){
                case SDLK_ESCAPE:
                    Application::instance()->quit(0);
                    break;
                case SDLK_RETURN:
                    if(!game()) {
                        randomize();
                        draw();
                    }
                    break;
                default:break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(windowID() == event->button.windowID)
            if(event->button.button == SDL_BUTTON_LEFT) {
                if(game()) {
                    move(event->button.x/sQuadre, event->button.y/sQuadre);
                    draw();
                    if(!game())
                        Message("Done",
                                "You are winner!\n Press <ENTER> for new game");
                }
            }
            break;
        default:
            break;
    }
    return result;
}

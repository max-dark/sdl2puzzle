//
// Created by max on 20.05.16.
//

#include <random>
#include <iostream>
#include "Application.h"
#include "GameWindow.h"
#include <SDL2/SDL_image.h>


GameWindow::~GameWindow() {
    SDL_FreeSurface(img);
    SDL_DestroyTexture(tex);
}

GameWindow::GameWindow(const char* title) : SimpleWindow(title, kCellSize * kNumCells, kCellSize * kNumCells),
                                            rnd() {
    initTexture();
    initRects();
    randomize();
    draw();
    show();
}

int GameWindow::Message(const char * title, const char * message, Uint32 flags = SDL_MESSAGEBOX_INFORMATION) {
    return SDL_ShowSimpleMessageBox(
        flags,
        title,
        message,
        handle()
    );
}

void GameWindow::initTexture() {
    const char tex_file[] = "./cells.bmp";

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
void GameWindow::initRects() {
    for(uint8_t i=1; i < kNumCells * kNumCells; ++i) {
        positions[i - 1].h = kCellSize;
        positions[i - 1].w = kCellSize;
        positions[i - 1].x = (i % kNumCells) * kCellSize;
        positions[i - 1].y = (i / kNumCells) * kCellSize;
    }
    positions[15].h = kCellSize;
    positions[15].w = kCellSize;
    positions[15].x = 0;
    positions[15].y = 0;
}

void GameWindow::randomize() {
    size_t i, j;
    int num = 0;

    for (i=0; i < kNumCells; ++i)
        for (j=0; j < kNumCells; ++j)
            cells[i][j]=-1;
    do {
        i = rnd() % kNumCells;
        j = rnd() % kNumCells;
        if(cells[i][j] == -1) {
            cells[i][j]=num;
            ++num;
        }
    }
    while(num<16);
}

void GameWindow::move(int x, int y) {
    if(cells[x][y] == kEmptyCellId)
        return;
    for(int i = x-1; i<=x+1; ++i) {
        if(i<0) continue;
        if(i >= kNumCells) continue;
        for(int j = y-1; j<=y+1; ++j) {
            if(j<0) continue;
            if(j >= kNumCells) continue;
            if(abs(x-i) == abs(y-j)) continue;
            if(cells[i][j] == kEmptyCellId) {
                cells[i][j] = cells[x][y];
                cells[x][y] = kEmptyCellId;
                return;
            }
        }
    }
}

bool GameWindow::game() {
    int num = 0;
    int i,j;
    for (i=0; i < kNumCells; ++i)
        for (j=0; j < kNumCells; ++j) {
            if(cells[i][j] != num)
                return true;
            ++num;
        }
    return false;
}

void GameWindow::draw() {
    SDL_Rect rc = {0, 0, kCellSize, kCellSize};
    SDL_SetRenderDrawColor(render(), 255, 255, 255, 255);
    SDL_RenderClear(render());

    for(int i=0; i < kNumCells; ++i) {
        rc.x = kCellSize * i;
        for(int j=0; j < kNumCells; ++j) {
            rc.y = kCellSize * j;
            SDL_RenderCopy(render(), tex, &positions[cells[i][j]], &rc);
        }
    }
    SDL_RenderPresent(render());
}

bool GameWindow::processEvent(const SDL_Event* event) {
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
                    move(event->button.x / kCellSize, event->button.y / kCellSize);
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

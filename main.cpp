/* 
 * File:   main.cpp
 * Author: max
 *
 * Created on 29 Октябрь 2013 г., 12:11
 */

#include "Application.h"
#include "SimpleWindow.h"
#include "GameWindow.h"
#include <iostream>

int main(int argc, char** argv) {
    Application* app = Application::instance();
    if(!app->init(argc, argv)) {
        std::cout << SDL_GetError() << std::endl;
        return -1;
    }
    GameWindow win("Puzzle in SDL2");
    if(win.handle() == nullptr) {
        std::cout << SDL_GetError() << std::endl;
        app->quit(-2);
    }
    return app->exec();
}


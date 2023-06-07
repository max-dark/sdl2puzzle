/* 
 * File:   Application.cpp
 * Author: max
 * 
 * Created on 29 Октябрь 2013 г., 16:12
 */

#include "Application.h"

bool Application::init(int, char**, Uint32 flags) {
    exitcode = SDL_Init(flags);
    running = (exitcode == 0);
    return running;
}

int Application::exec() {
    SDL_Event event;
    bool processed;
    
    while(running) {
        while(SDL_PollEvent(&event)) {
            processed = nullptr != dispatch(&event);
            if((event.type == SDL_QUIT) &&
               !processed)
                quit(exitcode);
        }
        idle();
        SDL_Delay(1);
    }
    cleanup();
    SDL_Quit();
    return exitcode;
}

Application::~Application(){
    cleanup();
}

Application * Application::instance() {
    static Application app;
    return &app;
}

void Application::quit(int code=0) {
    exitcode = code;
    running = false;
}
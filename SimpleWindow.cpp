/* 
 * File:   SimpleWindow.cpp
 * Author: max
 * 
 * Created on 29 Октябрь 2013 г., 19:01
 */

#include "SimpleWindow.h"

SimpleWindow::SimpleWindow() {
    createWindow("Simple Window",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            640, 480,0);
}

SimpleWindow::SimpleWindow(const char* title, Uint32 flags) {
    createWindow(title,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            640, 480, flags);
}

SimpleWindow::SimpleWindow(const char *title,
                 int width, int height, Uint32 flags) {
    createWindow(title,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            height, width, flags);
}

SimpleWindow::SimpleWindow(const char *title,
        int x, int y, int width, int height, Uint32 flags) {
    createWindow(title,
            x, y, height, width, flags);
}

SimpleWindow::~SimpleWindow() {
    if(m_window) {
        Application::instance()->deleteListener(this);
        SDL_DestroyRenderer(m_render);
        SDL_DestroyWindow(m_window);
    }
}

bool SimpleWindow::processEvent(const SDL_Event*) {
    return false;
}

void SimpleWindow::createWindow(const char *title,
        int x, int y, int width, int height, Uint32 flags) {
    m_window = SDL_CreateWindow(title, x, y, width, height, flags | SDL_WINDOW_HIDDEN);
    if(m_window) {
        m_flags = flags;
        m_wID = SDL_GetWindowID(m_window);
        m_render = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_SOFTWARE);
        Application::instance()->addListener(this);
    }
}

SDL_Window *SimpleWindow::handle() { return m_window; }

SDL_Renderer *SimpleWindow::render() { return m_render; }

void SimpleWindow::show() { SDL_ShowWindow(m_window); }

void SimpleWindow::hide() { SDL_HideWindow(m_window); }

Uint32 SimpleWindow::windowID() { return m_wID; }
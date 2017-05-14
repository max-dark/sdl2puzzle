/* 
 * File:   SimpleWindow.h
 * Author: Cra3y
 *
 * Created on 29 Октябрь 2013 г., 19:01
 */

#ifndef SIMPLEWINDOW_H
#define	SIMPLEWINDOW_H

#include "Application.h"
#include "IEventListener.h"

class SimpleWindow:public IEventListener {
public:
    SimpleWindow();
    SimpleWindow(const char *title, Uint32 flags=0);
    SimpleWindow(const char *title,
		    int width, int height, Uint32 flags=0);
    SimpleWindow(const char *title,int x, int y,
		    int width, int height, Uint32 flags=0);
    virtual ~SimpleWindow();
    virtual bool processEvent(const SDL_Event*);
	SDL_Window * handle();
	SDL_Renderer * render();
	void show();
	void hide();
	Uint32 windowID();
protected:
    void createWindow(const char *title,int x, int y,
		    int width, int height, Uint32 flags);
private:
    SDL_Window*   m_window;
    SDL_Renderer* m_render;
    Uint32        m_wID, m_flags;
};

#endif	/* SIMPLEWINDOW_H */


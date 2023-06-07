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
    explicit SimpleWindow(const char *title, Uint32 flags = 0);
    SimpleWindow(const char *title,
		    int width, int height, Uint32 flags=0);
    SimpleWindow(const char *title,int x, int y,
		    int width, int height, Uint32 flags=0);
    ~SimpleWindow() override;
    bool processEvent(const SDL_Event*) override;
	SDL_Window * handle();
	SDL_Renderer * render();
	void show();
	void hide();
	[[nodiscard]]
    Uint32 windowID() const;
protected:
    void createWindow(const char *title,int x, int y,
		    int width, int height, Uint32 flags);
private:
    SDL_Window*   m_window = nullptr;
    SDL_Renderer* m_render = nullptr;
    Uint32 m_flags = 0;
    Uint32 m_wID = 0;
};

#endif	/* SIMPLEWINDOW_H */


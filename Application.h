/* 
 * File:   Application.h
 * Author: max
 *
 * Created on 29 Октябрь 2013 г., 16:12
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

#include "EventDispatcher.h"

class Application: public EventDispatcher {
public:
	static Application * instance();
	bool init(int, char**, Uint32 flags = SDL_INIT_VIDEO);
	void quit(int);
    int exec();
protected:
    virtual void cleanup() {}
private:
    bool runned;
    int  exitcode;
    Application():runned(false),
        exitcode(0) {}
    virtual ~Application();
};

#endif	/* APPLICATION_H */


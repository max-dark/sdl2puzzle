/* 
 * File:   IBaseEvent.h
 * Author: Cra3y
 *
 * Created on 29 Октябрь 2013 г., 12:17
 */

#ifndef IEVENTLISTENER_H
#define	IEVENTLISTENER_H

#include <SDL2/SDL.h>
/**
 * @brief Слущатель сообщений от диспетчера
 */
class IEventListener {
public:
    /**
     * @brief Обработка сообщения
     * @param Сообщение
     * @return true - если сообщение обработано false если его над послать дальше
     */
    virtual bool processEvent(const SDL_Event*) = 0;

    virtual void processIdle(void);

    IEventListener();
    virtual ~IEventListener();

    Uint32 id(); /// получить индификатор
    Uint32 id(Uint32 ID); /// Установить идификатор, вернуть старый
private:
    Uint32 mID;
    static Uint32 sID;
};

#endif	/* IBASEEVENT_H */


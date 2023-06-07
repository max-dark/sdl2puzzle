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
 * @brief Слушатель сообщений от диспетчера
 */
class IEventListener {
public:
    /**
     * @brief Обработка сообщения
     * @param event Сообщение
     * @return true - если сообщение обработано false если его над послать дальше
     */
    virtual bool processEvent(const SDL_Event* event) = 0;

    virtual void processIdle();

    IEventListener();
    virtual ~IEventListener();

    [[nodiscard]]
    Uint32 id() const; /// получить идентификатор
    Uint32 id(Uint32 ID); /// Установить идентификатор, вернуть старый
private:
    Uint32 mID;
    static Uint32 sID;
};

#endif	/* IEVENTLISTENER_H */


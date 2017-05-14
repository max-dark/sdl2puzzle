/* 
 * File:   EventProcessor.h
 * Author: max
 *
 * Created on 29 Октябрь 2013 г., 12:38
 */

#ifndef EVENTDISPARCHER_H
#define	EVENTDISPARCHER_H

#include <vector>
#include <SDL2/SDL.h>
#include "IEventListener.h"
/**
 * @brief Перенаправляет сообщение слушателям
 */
class EventDispatcher {
public:
    /**
     * @brief добавляет слушателя в список, если его еще там нет
     * @param указатель на слушателя
     */
    void addListener(IEventListener *);
    /**
     * @brief Удаляет слушателя из списка
     * @param указатель на слушателя
     */
    void deleteListener(const IEventListener*);
    /**
     * @brief Заменяет слушателя на другого.
     * Не меняет, если параметры равны.
     * Если первый не найден то хз что делать.
     * И не известно что делать если 2й уже есть в списке
     * На данный момент не делаем ничего
     * @param кого менять
     * @param на кого менять
     */
    void replaceListener(const IEventListener *, IEventListener *);
    /**
     * @brief Отправка сообщения
     * @param сообщение
     * @return если сообщение обработано то указатель на обработавшего, иначе NULL
     */
    IEventListener* dispatch(const SDL_Event*) ;
    /**
     * @brief Посылает каждому из списка сообщение "простой"
     */
    void idle();
    virtual ~EventDispatcher();
private:
    typedef std::vector<IEventListener*> EventVector;
    typedef EventVector::const_iterator const_iterator;
    typedef EventVector::iterator       iterator;
    EventVector m_listeners; /// Список слушателей
};

#endif	/* EVENTPROCESSOR_H */


/* 
 * File:   EventProcessor.cpp
 * Author: max
 * 
 * Created on 29 Октябрь 2013 г., 12:38
 */

#include "EventDispatcher.h"
#include <algorithm>
#include <iostream>

void EventDispatcher::addListener(IEventListener* that) {
    
    if(that == nullptr)
        return;
    auto it = std::find(m_listeners.begin(), m_listeners.end(), that);

    if (it != m_listeners.end())
    {
        return;
    }
    m_listeners.push_back(that);
}

void EventDispatcher::deleteListener(const IEventListener* that) {
    auto it = std::remove(m_listeners.begin(), m_listeners.end(), that);
    m_listeners.erase(it, m_listeners.end());
}

void EventDispatcher::replaceListener(const IEventListener *that,
                                      IEventListener *to) {
    if(that == to)
        return;
    auto it = std::find(m_listeners.begin(), m_listeners.end(), that);
    if (it != m_listeners.end()) {
        *it = to;
    }
}

IEventListener* EventDispatcher::dispatch(const SDL_Event* event) {
    
    for( auto  listener : m_listeners) {
        if(listener->processEvent(event)) {
            return listener;
        }
    }
    return (nullptr);
}

void EventDispatcher::idle() {

    for( auto  listener : m_listeners) {
        listener->processIdle();
    }
}

EventDispatcher::~EventDispatcher() = default;

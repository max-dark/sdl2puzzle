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
	
	if(that == NULL)
		return;
	const_iterator it = m_listeners.begin();
	
	while (it != m_listeners.end()) {
		if(*it == that)
			return;
		++it;
	}
	m_listeners.push_back(that);
}

void EventDispatcher::deleteListener(const IEventListener* that) {
	iterator it = m_listeners.begin();
	
	while (it != m_listeners.end()) {
		if(*it == that) {
			m_listeners.erase(it);
			return;
		}
		++it;
	}
}

void EventDispatcher::replaceListener(const IEventListener *that,
									  IEventListener *to) {
	if(that == to)
		return;
	iterator it = m_listeners.begin();
	
	while (it != m_listeners.end()) {
		if(*it == that) {
			*it = to;
			return;
		}
		++it;
	}
}

IEventListener* EventDispatcher::dispatch(const SDL_Event* event) {
	IEventListener* listener = NULL;
    iterator it = m_listeners.begin();
	
	for(; it != m_listeners.end(); ++it) {
        listener = *it;
		if(listener->processEvent(event)) {
			return listener;
		}
	}
	return (NULL);
}

void EventDispatcher::idle() {
	const_iterator it = m_listeners.begin();

	while(it != m_listeners.end()) {
        (*it)->processIdle();
		++it;
	}
}

EventDispatcher::~EventDispatcher() {}

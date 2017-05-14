#include "IEventListener.h"

Uint32 IEventListener::sID = 0; // счетчик объектов, индификатор по умолчанию

IEventListener::~IEventListener() {}

Uint32 IEventListener::id() { return mID; }

Uint32 IEventListener::id(Uint32 ID) {
    Uint32 old = mID;
    mID = ID;
    return old;
}

void IEventListener::processIdle(void) {}

IEventListener::IEventListener() { mID = sID++;}
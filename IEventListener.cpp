#include "IEventListener.h"

Uint32 IEventListener::sID = 0; // счетчик объектов, идентификатор по умолчанию

IEventListener::~IEventListener() = default;

Uint32 IEventListener::id() const { return mID; }

Uint32 IEventListener::id(Uint32 ID) {
    Uint32 old = mID;
    mID = ID;
    return old;
}

void IEventListener::processIdle() {}

IEventListener::IEventListener() { mID = sID++;}
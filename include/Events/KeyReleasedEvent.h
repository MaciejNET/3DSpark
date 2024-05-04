#ifndef INC_2DSPARK_KEYRELEASEDEVENT_H
#define INC_2DSPARK_KEYRELEASEDEVENT_H

#include "Event.h"

class KeyReleasedEvent : public Event
{
public:
    KeyReleasedEvent() = default;
    KeyReleasedEvent(int key) : _key(key) {};
    const EventType GetType() const override { return EventType::KeyReleased; };
    int GetKey() const { return _key; };

private:
    int _key;
};

#endif //INC_2DSPARK_KEYRELEASEDEVENT_H

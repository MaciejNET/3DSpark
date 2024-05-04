#ifndef INC_2DSPARK_KEYPRESSEDEVENT_H
#define INC_2DSPARK_KEYPRESSEDEVENT_H

#include "Event.h"

class KeyPressedEvent : public Event
{
public:
    KeyPressedEvent() = default;
    explicit KeyPressedEvent(int key) : _key(key) {};
    const EventType GetType() const override { return EventType::KeyPressed; }
    int GetKey() const { return _key; }

private:
    int _key;
};

#endif //INC_2DSPARK_KEYPRESSEDEVENT_H

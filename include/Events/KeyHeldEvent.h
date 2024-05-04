#ifndef INC_2DSPARK_KEYHELD_EVENT_H
#define INC_2DSPARK_KEYHELD_EVENT_H

#include "Event.h"

class KeyHeldEvent : public Event
{
public:
    KeyHeldEvent() = default;
    explicit KeyHeldEvent(int key) : _key(key) {};
    const EventType GetType() const override { return EventType::KeyHeld; }
    int GetKey() const { return _key; }

private:
    int _key;
};

#endif //INC_2DSPARK_KEYHELD_EVENT_H

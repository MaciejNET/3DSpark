#ifndef INC_2DSPARK_MOUSEMOVEDEVENT_H
#define INC_2DSPARK_MOUSEMOVEDEVENT_H

#include "Event.h"

class MouseMovedEvent : public Event
{
public:
    MouseMovedEvent() = default;
    explicit MouseMovedEvent(float x, float y) : _x(x), _y(y) {};
    const EventType GetType() const override { return EventType::MouseMoved; }
    float GetX() const { return _x; }
    float GetY() const { return _y; }

private:
    float _x;
    float _y;
};

#endif //INC_2DSPARK_MOUSEMOVEDEVENT_H

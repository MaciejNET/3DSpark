#ifndef INC_2DSPARK_MOUSEBUTTONPRESSEDEVENT_H
#define INC_2DSPARK_MOUSEBUTTONPRESSEDEVENT_H

#include "Event.h"

class MouseButtonPressedEvent : public Event
{
public:
    MouseButtonPressedEvent(int button) : _button(button) {};
    const EventType GetType() const override { return EventType::MouseButtonPressed; };
    int GetButton() const { return _button; };

private:
    int _button;
};

#endif //INC_2DSPARK_MOUSEBUTTONPRESSEDEVENT_H

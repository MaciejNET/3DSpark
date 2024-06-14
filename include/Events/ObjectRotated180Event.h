#ifndef INC_3DSPARK_OBJECTROTATED180EVENT_H
#define INC_3DSPARK_OBJECTROTATED180EVENT_H

#include "Event.h"

class ObjectRotated180Event : public Event
{
public:
    ObjectRotated180Event() = default;

    const EventType GetType() const override { return EventType::ObjectRotated180; }
};

#endif //INC_3DSPARK_OBJECTROTATED180EVENT_H

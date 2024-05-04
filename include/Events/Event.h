#ifndef INC_2DSPARK_EVENT_H
#define INC_2DSPARK_EVENT_H

#include <functional>

enum class EventType
{
    None = 0,
    KeyPressed,
    MouseMoved,
    KeyHeld,
    KeyReleased,
    MouseButtonPressed
};

/**
 * Klasa reprezentująca zdarzenie
 */
class Event
{
public:
    /**
     * Konstruktor
     */
    Event() = default;

    /**
     * Destruktor
     */
    virtual ~Event() = default;

    /**
     * Metoda zwracająca typ zdarzenia
     * @return typ zdarzenia
     */
    virtual const EventType GetType() const = 0;
};

#endif //INC_2DSPARK_EVENT_H

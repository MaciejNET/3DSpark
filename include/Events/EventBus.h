#ifndef INC_2DSPARK_EVENTBUS_H
#define INC_2DSPARK_EVENTBUS_H

#include <unordered_map>
#include <memory>
#include <mutex>
#include "Event.h"

/**
 * Klasa reprezentująca event bus
 */
class EventBus
{
public:
    EventBus() = delete;
    ~EventBus() = delete;

    EventBus(const EventBus&) = delete;
    EventBus& operator=(const EventBus&) = delete;

    /**
     * Metoda do subskrybowania eventów
     * @tparam T typ eventu
     * @param func funkcja do wywołania
     */
    template<typename T, typename = std::enable_if_t<std::is_base_of_v<Event, T>>>
    static void Subscribe(std::function<void(T&)> func)
    {
        _handlers[T().GetType()].push_back([func](Event& event) { func(static_cast<T&>(event)); });
    }

    /**
     * Metoda do odsubskrybowania eventów
     * @tparam T typ eventu
     */
    template<typename T, typename = std::enable_if_t<std::is_base_of_v<Event, T>>>
    static void Unsubscribe()
    {
        auto eventType = T().GetType();
        auto it = _handlers.find(eventType);
        if (it != _handlers.end())
            it->second.clear();
    }

    /**
     * Metoda do publikowania eventów
     * @param event event do opublikowania
     */
    static void Publish(const std::shared_ptr<Event>& event);

    /**
     * Metoda do przetwarzania eventów
     */
    static void DispatchEvents();
private:
    static void DispatchEvent(Event& event);

private:
    static std::unordered_map<EventType, std::vector<std::function<void(Event&)>>> _handlers;
    static std::vector<std::shared_ptr<Event>> _events;
};

#endif //INC_2DSPARK_EVENTBUS_H

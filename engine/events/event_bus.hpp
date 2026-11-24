#ifndef ET_GAME_EVENT_BUS_HPP
#define ET_GAME_EVENT_BUS_HPP

#include <vector>

#include "engine/state/game_state.hpp"
#include "engine/events/domain_events.hpp"

namespace et_game {

class GameObserver {
public:
    virtual ~GameObserver() = default;
    virtual void on_event(const DomainEvent& event, const GameState& game_state) = 0;
};

class EventBus {
public:
    EventBus() = default;

    EventBus(const EventBus&) = delete;
    EventBus& operator=(const EventBus&) = delete;

    void subscribe(GameObserver& observer);
    void unsubscribe(GameObserver& observer);

    void publish(const DomainEvent& event, const GameState& game_state) const;

private:
    std::vector<GameObserver*> _observers{};
};

} // namespace et_game

#endif

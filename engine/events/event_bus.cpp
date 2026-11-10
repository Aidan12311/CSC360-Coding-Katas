#include <algorithm>

#include "engine/events/event_bus.hpp"

namespace et_game {

void EventBus::subscribe(GameObserver& observer) {
    if(std::find(_observers.begin(), _observers.end(), &observer) != _observers.end()) {
        return;
    }

    _observers.push_back(&observer);
}

void EventBus::unsubscribe(GameObserver& observer) {
    std::erase(_observers, &observer);
}

void EventBus::publish(const DomainEvent& event, const GameState& game_state) const {
    for(GameObserver *observer : _observers) {
        observer->on_event(event, game_state);
    }
}

} // namespace et_game

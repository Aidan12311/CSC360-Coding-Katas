#ifndef ET_GAME_SAVE_OBSERVER_HPP
#define ET_GAME_SAVE_OBSERVER_HPP

#include "engine/events/event_bus.hpp"
#include "engine/util/concurrent_queue.hpp"

namespace et_game {

class SaveObserver : public GameObserver {
public:
    explicit SaveObserver(SaveEventQueue& save_queue): _save_queue(save_queue) {}

    void on_event(const DomainEvent& event, const GameState& game_state) override;

private:
    SaveEventQueue& _save_queue;
};

} // namespace et_game

#endif

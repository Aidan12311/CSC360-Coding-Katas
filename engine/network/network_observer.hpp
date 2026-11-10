#ifndef ET_GAME_NETWORK_OBSERVER_HPP
#define ET_GAME_NETWORK_OBSERVER_HPP

#include "models/world.hpp"
#include "engine/events/event_bus.hpp"
#include "engine/util/concurrent_queue.hpp"

namespace et_game {

// Turns domain events into protocol messages for the connected client.
class NetworkObserver : public GameObserver {
public:
    NetworkObserver(const World& world, OutputQueue& output_queue):
        _world(world), _output_queue(output_queue) {}

    void on_event(const DomainEvent& event, const GameState& game_state) override;

private:
    const World& _world;
    OutputQueue& _output_queue;
};

} // namespace et_game

#endif

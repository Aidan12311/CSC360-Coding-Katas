#ifndef ET_GAME_GAME_LOOP_HPP
#define ET_GAME_GAME_LOOP_HPP

#include <optional>

#include "models/world.hpp"
#include "engine/state/game_state.hpp"
#include "engine/events/event_bus.hpp"
#include "engine/events/input_event.hpp"
#include "engine/util/concurrent_queue.hpp"

namespace et_game {

void handle_connect(
    const ConnectEvent& connect_event,
    const World& world,
    std::optional<GameState>& game_state,
    const EventBus& event_bus
);

void handle_disconnect(
    const DisconnectEvent& disconnect_event,
    std::optional<GameState>& game_state
);

void handle_game_event(
    const GameEvent& game_event,
    const World& world,
    std::optional<GameState>& game_state,
    const EventBus& event_bus
);

void tick(
    GameState& game_state,
    const World& world,
    double dt,
    const EventBus& event_bus
);

void run_game_loop(
    const World& world,
    InputQueue& input_queue,
    OutputQueue& output_queue,
    SaveEventQueue& save_queue
);

} // namespace et_game

#endif

#ifndef ET_GAME_GAME_LOGIC_HPP
#define ET_GAME_GAME_LOGIC_HPP

#include "models/world.hpp"
#include "engine/state/game_state.hpp"
#include "engine/events/event_bus.hpp"

namespace et_game {

void apply_movement_event(
    GameState& game_state,
    const World& world,
    double dt
);

bool handle_exit_transitions(
    GameState& game_state,
    const World& world,
    const EventBus& event_bus
);

void handle_pickup_collection(
    GameState& game_state,
    const World& world,
    const EventBus& event_bus
);

void drain_energy(GameState& game_state, const World& world, double dt);

void check_win_lose(
    GameState& game_state,
    const World& world,
    const EventBus& event_bus
);

} // namespace et_game

#endif

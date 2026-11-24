#ifndef ET_GAME_EVENT_HANDLERS_HPP
#define ET_GAME_EVENT_HANDLERS_HPP

#include <nlohmann/json.hpp>

#include "models/world.hpp"
#include "engine/state/game_state.hpp"
#include "engine/events/event_bus.hpp"

namespace et_game {

using Json = nlohmann::json;
using InputHandlerFn = void(*)(GameState&, const World&, const EventBus&, const Json&);

void dispatch_game_event(
    GameState& game_state,
    const World& world,
    const EventBus& event_bus,
    const Json& json_payload
);

void handle_move_event(
    GameState& game_state,
    const World& world,
    const EventBus& event_bus,
    const Json& json_payload
);

void handle_consume_candy_event(
    GameState& game_state,
    const World& world,
    const EventBus& event_bus,
    const Json& json_payload
);

} // namespace et_game

#endif

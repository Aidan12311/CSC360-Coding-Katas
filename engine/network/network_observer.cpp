#include <optional>

#include "engine/util/visitor.hpp"
#include "engine/network/network_observer.hpp"
#include "engine/protocol/message_builders.hpp"

namespace et_game {

void NetworkObserver::on_event(const DomainEvent& event, const GameState& game_state) {
    std::visit(Overloaded {
        [&](const SessionStarted&) {
            _output_queue.push(build_room_loaded(_world, game_state, std::nullopt));
        },
        [&](const RoomChanged& room_changed) {
            _output_queue.push(build_room_loaded(_world, game_state, room_changed.arrived_from));
        },
        [&](const GameWon&) {
            _output_queue.push(build_game_over(game_state));
        },
        [&](const GameLost&) {
            _output_queue.push(build_game_over(game_state));
        },
        [&](const TickCompleted&) {
            _output_queue.push(build_state_update(_world, game_state));
        },
        [](const auto&) { }
    }, event);
}

} // namespace et_game

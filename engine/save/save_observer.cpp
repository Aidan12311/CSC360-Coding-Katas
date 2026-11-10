#include "engine/util/visitor.hpp"
#include "engine/save/save_observer.hpp"
#include "engine/save/save_event_builder.hpp"

namespace et_game {

void SaveObserver::on_event(const DomainEvent& event, const GameState& game_state) {
    auto save = [&](const char* trigger) {
        _save_queue.push(build_save_event(game_state, trigger));
    };

    std::visit(Overloaded {
        [&](const RoomChanged&)      { save("exit_transition"); },
        [&](const PickupsCollected&) { save("pickup"); },
        [&](const CandyConsumed&)    { save("candy_consumed"); },
        [&](const GameWon&)          { save("win"); },
        [&](const GameLost&)         { save("lose"); },
        [](const auto&)              { }
    }, event);
}

} // namespace et_game

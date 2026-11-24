#ifndef ET_GAME_DOMAIN_EVENTS_HPP
#define ET_GAME_DOMAIN_EVENTS_HPP

#include <vector>
#include <variant>

#include "models/types.hpp"

namespace et_game {

struct SessionStarted {};

struct RoomChanged {
    Direction arrived_from{};
};

struct PickupsCollected {
    std::vector<PickupId> pickup_ids{};
};

struct CandyConsumed {};

struct GameWon {};

struct GameLost {};

struct TickCompleted {};

using DomainEvent = std::variant<
    SessionStarted,
    RoomChanged,
    PickupsCollected,
    CandyConsumed,
    GameWon,
    GameLost,
    TickCompleted
>;

} // namespace et_game

#endif

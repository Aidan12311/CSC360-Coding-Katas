#ifndef ET_GAME_SERVICE_WALKABILITY_STRATEGY_HPP
#define ET_GAME_SERVICE_WALKABILITY_STRATEGY_HPP

#include <string>

namespace et_game {

struct TileDef {
    bool walkable{false};
    std::string name{"Unknown Tile"};
};

struct WalkabilityStrategy {
    virtual ~WalkabilityStrategy() = default;
    virtual bool is_walkable(const TileDef& tile_def) const = 0;
};

struct TileDefWalkability : public WalkabilityStrategy {
    bool is_walkable(const TileDef& tile_def) const override {
        return tile_def.walkable;
    }
};

struct AllWalkable : public WalkabilityStrategy {
    bool is_walkable(const TileDef&) const override {
        return true;
    }
};

struct NoneWalkable : public WalkabilityStrategy {
    bool is_walkable(const TileDef&) const override {
        return false;
    }
};

} // namespace et_game

#endif
